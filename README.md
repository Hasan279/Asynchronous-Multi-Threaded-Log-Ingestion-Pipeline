# Asynchronous Multi-Threaded Log Ingestion Pipeline

An industrial-grade, multi-threaded log ingestion and parsing pipeline simulation built in C using POSIX threads (`pthread`), mutual exclusion locks (`pthread_mutex_t`), and semaphores (`sem_t`).

This project refactors a classic Producer-Consumer bounded-buffer problem into a real-world system architecture: simulated microservices (Producers) producing structured log messages and log indexers (Consumers) parsing and processing them.

---

## Architecture & Overview

In this system, concurrency and synchronization are managed over a shared bounded buffer containing structured `LogMessage` records:

- **Microservices (Producers)**: Generate structured logs concurrently and insert them into the shared buffer.
- **Log Indexers (Consumers)**: Retrieve logs from the shared buffer, parse, and index them.
- **Bounded Buffer**: A thread-safe, circular queue managing the log stream.
- **Synchronization primitives**:
  - `pthread_mutex_t`: Controls exclusive access to the shared buffer during insertion/removal operations.
  - `sem_t` (Empty Slots): Tracks the remaining space in the buffer to block producers when the buffer is full.
  - `sem_t` (Full Slots): Tracks the number of logs ready for processing to block consumers when the buffer is empty.

---

## Log Specification & Distribution

Logs are modeled as structured messages in memory:

```c
typedef struct {
    int service_id;      // ID of the generating service (1, 2, 3...)
    char log_level[8];   // "INFO", "WARN", or "ERROR"
    char message[64];    // Descriptive log message
} LogMessage;
```

An empty slot in the circular buffer is represented by a `service_id` of `-1`.

### Realistic Log Distribution
To simulate production environments, log levels and messages are randomly generated according to the following real-world distribution:
* **75% INFO**: `"User login successful"` (indicating normal operating events)
* **20% WARN**: `"Database connection pool low"` (indicating potential issues)
* **5% ERROR**: `"API request failed"` (indicating active service failures)

---

## Project Structure

```
producer-consumer-simulation/
├── main.c          # Entry point, thread orchestration, and simulation lifecycle
├── buffer.h        # Struct definitions, buffer size, and synchronization signatures
├── buffer.c        # Shared bounded buffer logic and thread safety implementation
├── Producer.h      # Producer thread function declarations
├── Producer.c      # Producer thread execution loop (generates logs)
├── Consumer.h      # Consumer thread function declarations
├── Consumer.c      # Consumer thread execution loop (processes logs)
├── logger.h        # Logger signatures and statistics tracker
├── logger.c        # Thread-safe console log output and final statistics summary
├── Makefile        # Compilation workflow targets
└── README.md       # Project documentation
```

---

## Requirements

* **Operating System**: Linux, macOS, or Windows Subsystem for Linux (WSL)
* **Compiler**: GCC
* **Libraries**: POSIX threads (`pthread`)

---

## Compilation

Build the executable using the provided `Makefile`:

```bash
make
```

Or manually invoke GCC:

```bash
gcc -o simulation main.c buffer.c Producer.c Consumer.c logger.c -lpthread
```

To clean build artifacts:

```bash
make clean
```

---

## Configuration & Scenarios

You can fine-tune and orchestrate different microservice workloads in [main.c](file:///c:/Users/dell/OneDrive/Documents/My%20Projects/Producer-Consumer-Simulation/main.c):

| Parameter | Location | Description | Default |
|---|---|---|---|
| `BUFFER_SIZE` | `buffer.h` | Bounded buffer slot capacity | `5` |
| `SIM_DURATION` | `main.c` | Lifecycle of the simulation in seconds | `15` |

### Simulation Scenarios
`main.c` contains multiple predefined test scenarios that can be toggled/configured:
1. **Scenario 1: Services generating logs (Producers only)** — Simulates log overflow where log ingestion is paused or indexers are down.
2. **Scenario 2: Single Producer & Single Consumer** — Simulates a basic 1:1 pipeline.
3. **Scenario 3: Multiple Consumers** — Simulates high indexer throughput.

---

## Sample Execution Output

Below is a sample run showcasing two active microservices generating logs and filling the bounded buffer:

```text
=== Asynchronous Multi-Threaded Log Ingestion Pipeline ===

Running: 2 Services generating logs
[0.0s] Service-1 generated [INFO]: User login successful | Buffer: [1/5 slots full]
[0.0s] Service-2 generated [WARN]: Database connection pool low | Buffer: [2/5 slots full]
[1.0s] Service-1 generated [INFO]: User login successful | Buffer: [3/5 slots full]
[1.0s] Service-2 generated [ERROR]: API request failed | Buffer: [4/5 slots full]
[2.0s] Service-1 generated [INFO]: User login successful | Buffer: [5/5 slots full]
...

==========================================
     Log Ingestion Pipeline Complete
==========================================
 Total Logs Generated : 30
 Total Logs Indexed   : 0
==========================================
```

If consumers (indexers) are active, you will see real-time extraction:
```text
[0.0s] Service-1 generated [INFO]: User login successful | Buffer: [1/5 slots full]
[0.0s] Indexer-1 processed [INFO]: User login successful | Buffer: [0/5 slots full]
```

---

## Core Systems Programming Concepts Demonstrated

* **POSIX Concurrency**: Multi-threaded execution model using `pthread_create` and `pthread_join`.
* **Bounded-Buffer Problem Solving**: Industrial implementation of classic producer-consumer sync using semaphores to coordinate production/consumption threads.
* **Mutual Exclusion**: Guarding the circular queue's read/write pointers and count updates using mutual exclusion locks (`pthread_mutex_t`).
* **Thread-Safe Logging**: Synchronized console prints using a central display lock (`print_mutex`) to prevent output interleaving.
* **Graceful Lifecycle Shutdown**: Orderly thread teardown signaling through a volatile control flag (`running`) combined with semaphore posting.

---

## Developers

| Name | GitHub Profile |
| :--- | :--- |
| Hasan Waseem | [@HasanWaseem](https://github.com/Hasan279) |
| Anas Khan | [@AnasKhan](https://github.com/AnasKhan-1) |
| Areeb Saeed | [@AreebSaeed](https://github.com/AreebSaeed) |
