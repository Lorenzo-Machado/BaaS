

# BaaS™ – BSOD as a SERVICE™
![Linguagem](https://img.shields.io/badge/Language-C-blue)
![Plataforma](https://img.shields.io/badge/Platform-Windows-critical)
![API](https://img.shields.io/badge/API-Totally%20Real%20Trust%20Me-green)
![Estabilidade](https://img.shields.io/badge/System%20Stability-Nonexistent-red)
</br>
![bsod](https://media.tenor.com/6sJQ9Q7wG9MAAAAd/blue-screen-windows.gif)
</br>
</br><sup>"a good software when a bad software is required."</sup></br>
**-John Computer**</br></br>

an absolutely unnecessary piece of software written in C whose only purpose in life is to expose an HTTP endpoint that **crashes your Windows machine on demand** 💀

yes... it's exactly what it sounds like.

---

## WHAT DOES THIS DO?

- starts a fake "web server"
- accepts any HTTP request
- returns a cute JSON error
- waits 5 seconds…
- **fucking kills your entire OS with a BSOD**

---

## HOW THE "API" WORKS

```

GET [http://localhost:666](http://localhost:666)

````

response:
```json
{"status":"error","message":"BSOD ativado","code":"0xC0000420"}
````

Then:

```
congratulations, your system is now dead
```

---

##  INTERNAL CHAOS EXPLANATION

### -- SERVER --

```
socket(AF_INET, SOCK_STREAM, 0);
bind(..., 666);
listen(...);
```

creates a totally legit enterprise-grade™ TCP server
listens on port **666** (highly professional number)

---

### -- REQUEST HANDLING --

```
recv(client, buffer, ...);
send(client, response, ...);
```

reads whatever garbage the client sends
responds with HTTP 500 because we believe in consistency

---

### -- DELAY BEFORE DESTRUCTION --

```
Sleep(5000);
```

gives you 5 seconds to rethink your life choices as a biological being

---

### -- PRIVILEGE ESCALATION --

```
RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled);
```

basically tells Windows:

> "hey bro, let me crash the system real quick"

---

### -- THE FUN PART (BSOD) --

```
NtRaiseHardError(... OPTION_SHUTDOWN_SYSTEM ...)
```

forces a **critical system error**
Windows goes:

```
NOPE.
```

→ BSOD

---

## FEATURES (not bugs dude)

* real-time system destruction
* REST API (i guess)
* 100% crash success rate (i only tested once, it crashed once)
* zero recovery
* enterprise-ready (please don't)

---

## USE CASES (TOTALLY VALID)

* chaos engineering (extreme edition)
* testing how fast you can reboot
* ruining your own presentation
* get a free talk with that hot HR lady
* getting fired speedrun any% no cheats 

---

## ROADMAP

* [ ] kubernetes BSOD operator 
* [ ] load balancer for multiple crashes
* [ ] SaaS version (BSOD-as-a-Subscription™)
* [ ] cloud deployment (aws goes brrrr)
* [ ] mobile support (android kernel panic... somewhen)

---

##  WARNING

</br>
THIS WILL ACTUALLY CRASH YOUR SYSTEM, like, fr
</br></br>

* do NOT run on your main machine (i ran and regret it)
* do NOT run during work 
* do NOT run if you enjoy your data
* do NOT run if you fear consequences (like a pussy)

</br>

I AM NOT RESPONSIBLE FOR:

* lost work
* corrupted files
* emotional damage
* angry bosses
* existential crises

---

## TECH STACK

* C (God's chosen language)
* Windows Native API (Nt* black magic)
* Winsock
* Bad decisions
* retardation

---

## DISCLAIMER

this project is for **educational and experimental purposes only**.
if you use this in production, that's on you dude, like, what can i even say?

---
