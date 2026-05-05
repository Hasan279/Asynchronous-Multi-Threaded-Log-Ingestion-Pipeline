# producer-consumer-simulation

A multi-threaded Producer-Consumer simulation built in C using POSIX threads, mutexes, and semaphores.

---

## Overview

Multiple producer threads generate random items and insert them into a shared bounded buffer. Multiple consumer threads simultaneously remove and process those items. Synchronization is handled using:

- **Mutex** — ensures only one thread accesses the buffer at a time
- **Semaphores** — track available empty and full slots to prevent overflow and underflow

The simulation runs for a configurable duration and prints a live timestamped log of all thread activity, followed by a final summary.

---

## Project Structure

```
producer-consumer-simulation/
├── main.c          # Entry point, thread creation, shutdown
├── buffer.h        # Buffer definitions and function declarations
├── buffer.c        # Shared buffer, mutex, semaphore logic
├── producer.h      # Producer thread declaration
├── producer.c      # Producer thread function
├── consumer.h      # Consumer thread declaration
├── consumer.c      # Consumer thread function
├── logger.h        # Logger declaration
├── logger.c        # Timestamped console logging
├── Makefile        # Build configuration
└── README.md       # Project documentation
```

---

## Requirements

- Linux / WSL / macOS
- GCC compiler
- POSIX threads (`pthread`) library

---

## How to Compile

```bash
make
```

Or manually:

```bash
gcc -o simulation main.c buffer.c producer.c consumer.c logger.c -lpthread
```

---

## How to Run

```bash
./simulation
```

You can configure the following values inside `main.c`:

| Parameter | Description | Default |
|---|---|---|
| `BUFFER_SIZE` | Maximum items in buffer | 5 |
| `NUM_PRODUCERS` | Number of producer threads | 3 |
| `NUM_CONSUMERS` | Number of consumer threads | 3 |
| `SIM_DURATION` | Simulation duration in seconds | 10 |

---

## Sample Output

```
[0.1s] Producer-1 inserted:  42  | Buffer: [42, -, -, -, -]
[0.2s] Producer-2 inserted:  17  | Buffer: [42, 17, -, -, -]
[0.3s] Consumer-1 removed:   42  | Buffer: [-, 17, -, -, -]
[0.5s] Producer-3 inserted:  88  | Buffer: [-, 17, 88, -, -]
...
--- Simulation Complete ---
Total Produced : 38
Total Consumed : 38
```

---

## Concepts Demonstrated

- POSIX thread creation and joining (`pthread_create`, `pthread_join`)
- Mutex locks (`pthread_mutex_t`)
- Semaphore-based synchronization (`sem_wait`, `sem_post`)
- Race condition prevention
- Graceful thread shutdown

---

## Developers

| Name | GitHub |
|------|--------|
| HasanWaseem | [@HasanWaseem](https://github.com/Hasan279) |
| AnasKhan | [@AnasKhan](https://github.com/AnasKhan-1) |
| AreebSaeed | [@AreebSaeed](https://github.com/AreebSaeed) |

---
