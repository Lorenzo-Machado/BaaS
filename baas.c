#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef NTSTATUS(NTAPI *pRtlAdjustPrivilege)(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN CurrentThread,
    PBOOLEAN Enabled
);

typedef NTSTATUS(NTAPI *pNtRaiseHardError)(
    NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters,
    ULONG ValidResponseOption,
    PULONG Response
);

#define SE_SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN_SYSTEM 6

int main(void) {
    printf("=== BAAS - BSOD as a Service™ ===\n");
    printf("servidor rodando na porta 666...\n");
    printf("qualquer requisição vai tentar causar um BSOD glorioso.\n\n");
    printf("AVISO: issaq vai crashar o Ruindows de verdade, sem meme, use por sua conta e risco\n\n");

    // carrega as funçáo td do ntdll
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    if (!ntdll) {
        printf("Falha ao carregar ntdll.dll\n");
        return 1;
    }

    pRtlAdjustPrivilege RtlAdjustPrivilege = (pRtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    pNtRaiseHardError NtRaiseHardError = (pNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");

    if (!RtlAdjustPrivilege || !NtRaiseHardError) {
        printf("Falha ao obter endereços das funções Nt*\n");
        return 1;
    }

    // cria um socket Ttcp simples pra servir como "API"
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        printf("Falha ao criar socket\n");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(666);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("Falha ao fazer bind na porta 666\n");
        closesocket(server);
        return 1;
    }

    listen(server, SOMAXCONN);
    printf("BAAS pronto acesse http://localhost:666 ou qualquer porta 666 para o crash.\n");

    while (1) {
        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET) continue;

        // lê a requisição (não importa o que seja)
        char buffer[1024];
        recv(client, buffer, sizeof(buffer)-1, 0);

        // responde algo bonitinho 
        const char *response = "HTTP/1.1 500 Internal Server Error\r\n"
                               "Content-Type: application/json\r\n\r\n"
                               "{\"status\":\"error\",\"message\":\"BSOD ativado\",\"code\":\"0xC0000420\"}\r\n";

        send(client, response, (int)strlen(response), 0);
        closesocket(client);

        printf("[BAAS] Requisição recebida → Iniciando BSOD em 5 segundos...\n");

        Sleep(5000);  // da uns segundim pra ver a resposta

        // o momento tao esperado
        BOOLEAN enabled;
        ULONG responseCode;

        RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled);
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, OPTION_SHUTDOWN_SYSTEM, &responseCode);

        // se chegar aqui, algo deu mais errado doq deveria (muito raro)
        printf("Falha ao causar BSOD. Tente novamente.\n");
    }

    return 0;
}
