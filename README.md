*This project has been created as part of the 42 curriculum by stmuller.*

# Minitalk

## Description

Minitalk is a small data exchange program using UNIX signals. It consists of two executables — a **server** and a **client** — that communicate exclusively through `SIGUSR1` and `SIGUSR2` signals.

The server starts first, prints its PID, and waits for incoming messages. The client connects to the server by passing the server's PID and a string as arguments, then encodes and transmits the string bit by bit using signals. The server reconstructs and prints the message once fully received.

Key design decisions:
- The string length is transmitted first (as `sizeof(size_t) * 8` bits) so the server can pre-allocate the buffer with `ft_calloc`.
- Each bit is acknowledged by the server with `SIGUSR2` before the client sends the next one, ensuring no signal is lost.
- The server tracks the sender's PID via `siginfo_t`, allowing it to reject concurrent clients by responding with `SIGUSR1` (busy signal) until the current transmission is complete.
- A single global variable is used per program: `g_client` (client) and `g_server` (server), both justified by the need to share state between the main loop and signal handlers.

## Instructions

### Compilation

```bash
make        # builds both client and server
make clean  # removes object files
make fclean # removes object files and executables
make re     # full recompile
```

### Execution

Start the server in one terminal:
```bash
./server
# prints its PID, e.g.: 12345
```

Send a message from another terminal:
```bash
./client 12345 "Hello, World!"
```

The server will print the received string. Multiple clients can send messages in sequence without restarting the server.

## Resources

### Documentation & References
- [`signal(7)` — Linux man page](https://man7.org/linux/man-pages/man7/signal.7.html)
- [`sigaction(2)` — Linux man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [`kill(2)` — Linux man page](https://man7.org/linux/man-pages/man2/kill.2.html)
- [UNIX Signals — Wikipedia](https://en.wikipedia.org/wiki/Signal_(IPC))
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/)

### AI Usage
AI (Claude) was used during this project for the following tasks:
- Clarifying edge cases around signal delivery on Linux (non-queuing behavior).
- Generating this README.

All AI-generated content was reviewed, tested, and validated before inclusion. The core implementation logic — bit encoding, the handshake protocol, and the server state machine — was written and understood independently.
