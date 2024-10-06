# Project Readers-Writers Synchronization 
## Overview
This project implements the Readers-Writers synchronization problem, ensuring that concurrent access to shared data is handled correctly without causing starvation for either readers or writers. The system is implemented using POSIX semaphores and shared memory segments, and it allows multiple processes to read and write from a shared binary file of customer records. The project demonstrates synchronization techniques to prevent issues like data races and starvation.

## Components
The project is divided into multiple components for modularity and ease of development. Below is a description of each file:

### 1. Source Files
- `src/semaphores.c`: Contains functions for managing semaphores, including creating, waiting, signaling, and destroying them. The functions utilize `semget`, `semop`, and `semctl` system calls for handling semaphores.
- `src/shared_memory.c`: Implements functions to create, attach, detach, and destroy shared memory segments. It uses `shmget`, `shmat`, `shmdt`, and `shmctl` for managing shared memory.
- `src/writer.c`: This program updates specific records in the shared file. It utilizes semaphores to enter a critical section before writing. It takes command-line arguments for specifying the record to be modified, the value to update, and the duration of the sleep time. It ensures only one writer updates a record at any time.
- `src/reader.c`: This program reads specific records from the shared file. It uses semaphores to enter a critical section before reading each record, ensuring synchronization with other readers and writers. The program takes command-line arguments for specifying the records to be read, the duration of the sleep time, and the shared memory ID for synchronization.
### 2. Header Files
- `include/semaphores.h`: Contains declarations for semaphore-related functions, ensuring modular code and separation of implementation from definition.
- `include/shared_memory.h`: Defines the SharedMemory and Record structures used throughout the project. It also contains function prototypes for shared memory operations.
### 3. Build and Object Files
- `build/`: Contains executables (reader and writer) created from the respective source files.
- `obj/`: Contains the compiled object files for each source file.
### 4. Tests
- `tests/`: Contains several binary data files (`accounts50.bin`, `accounts5000.bin`, etc.) used for testing the reader and writer programs. These files simulate different sizes of customer records for performance testing.
### 5. Makefile
The **Makefile** automates the compilation of the source files into object files and linking them to create the final executables. It also handles cleaning the build directory.

## Functionality
### Shared Data Structure
The shared memory segment contains:
- `Record:` Represents a customer record with fields such as `id`, `first_name`, `last_name`, and `balance`.
- `SharedMemory`: Stores an array of `Record` objects, and counters for the number of readers and writers for each record.
### Synchronization Mechanism
- **POSIX Semaphores** are used to synchronize access to shared memory:
    - `semaphore_wait` (`P()` operation) ensures mutual exclusion for writers.
    - `semaphore_signal` (`V()` operation) releases the semaphore after a writer completes its update.
### Writer Process (`writer.c`)
- The writer modifies a specific record by adding a given value to its balance.
- It takes command-line arguments:
    - `-f`: The filename of the binary file containing records.
    - `-l`: The ID of the record to modify.
    - `-v`: The value to be added or subtracted from the record's balance.
    - `-d`: The duration to simulate the writing process.
    - `-s`: The shared memory key for synchronization.

The writer first locks the semaphore for the record, updates it, and finally unlocks the semaphore.

### Reader Process (`reader.c`)
- The reader reads specific records from the shared file.
- It takes command-line arguments:
    - `-f`: The filename of the binary file containing records.
    - `-l`: The IDs of the records to read (comma-separated).
    - `-d`: The duration to simulate reading.
    - `-s`: The shared memory key for synchronization.

The reader first locks the semaphore for each record, reads it, and finally unlocks the semaphore. Multiple readers can access the same record concurrently, while writers have exclusive access.

## Compilation
To compile the project, use the command:

```console
make
```

This will compile all source files and generate the executable programs in the `build/` directory.

## Usage
The executables can be run with the following command-line syntax:

### Writer

```console
./writer -f filename -l recid -v value -d time -s shmid
```

- `filename`: Path to the binary file of records.
- `recid`: Record ID to modify.
- `value`: Value to update the balance by.
- `time`: Duration (in seconds) to simulate writing.
- `shmid`: Shared memory key for synchronization.

### Reader

```console
./reader -f filename -l recid[,recid] -d time -s shmid
```

- `filename`: Path to the binary file of records.
- `recid[,recid]`: Comma-separated list of record IDs to read.
- `time`: Duration (in seconds) to simulate reading.
- `shmid`: Shared memory key for synchronization.

## Cleanup 

To clean the project, use:

```console
make clean
```

**Note:** This project is the 3rd assignment of Operating Systems 2023-24 (K22) course of DIT NKUA.
