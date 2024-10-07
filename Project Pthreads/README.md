# Project Pthreads Demonstration

This project contains eight C programs that demonstrate various uses of POSIX Threads (Pthreads) for multithreading in C. The examples range from simple thread creation to more complex synchronization problems and parallel computation.

## Table of Contents

- Introduction
- Programs
    - Basic Programs
        - Basic Thread Creation and Joining
        - Thread Synchronization Using Mutex
        - Producer-Consumer Problem Using Condition Variables
        - Matrix Multiplication Using Multiple Threads
    - Advanced Programs
        - Thread Pool Implementation
        - Parallel Merge Sort
        - Dining Philosophers Problem
        - Threaded Matrix Multiplication with Dynamic Memory Allocation
- Compilation and Execution
- Requirements

## Introduction
POSIX Threads (Pthreads) is a powerful API that allows for multithreading in C. This project contains both basic and advanced examples of Pthreads usage, demonstrating thread creation, synchronization using mutexes and condition variables, and parallel computation with multithreading.

## Programs
### Basic Programs
1. **Basic Thread Creation and Joining**
    - **Filename:** `basic_thread_creation.c`
    - **Description:** Demonstrates how to create and join multiple threads using `pthread_create()` and `pthread_join()`.
2. **Thread Synchronization Using Mutex**
    - **Filename:** `thread_synchronization_mutex.c`
    - **Description:** Demonstrates thread synchronization using mutexes to protect a shared counter.
3. **Producer-Consumer Problem Using Condition Variables**
    - **Filename:** `producer_consumer_problem.c`
    - **Description:** Implements the producer-consumer problem using condition variables to synchronize access to a shared buffer.
4. **Matrix Multiplication Using Multiple Threads**
    - **Filename:** `matrix_multiplication_threads.c`
    - **Description:** Performs matrix multiplication using multiple threads, where each thread computes one row of the result matrix.
### Advanced Programs
5. **Thread Pool Implementation**
    - **Filename:** `thread_pool_implementation.c`
    - **Description:** Demonstrates a thread pool where a fixed number of threads are created and re-used to handle multiple tasks in a queue.
6. **Parallel Merge Sort**
    - **Filename:** `parallel_merge_sort.c`
    - **Description:** Implements the merge sort algorithm using multiple threads to parallelize sorting.
7. **Dining Philosophers Problem**
    - **Filename:** `dining_philosophers_problem.c`
    - **Description:** Solves the dining philosophers problem using threads, mutexes, and condition variables to synchronize the philosophers.
8. **Threaded Matrix Multiplication with Dynamic Memory Allocation**
    - **Filename:** `threaded_matrix_multiplication_dynamic.c`
    - **Description:** Performs matrix multiplication using multiple threads and dynamically allocated matrices.
## Compilation and Execution
To compile and run any program, use the following commands:

1. Compile the program:
```console
gcc -pthread -o <output_file> <source_file>.c
```

For example:

```console
gcc -pthread -o basic_thread_creation basic_thread_creation.c
```

2. Run the program:
```console
./<output_file>
```

## Requirements
- A C compiler with Pthreads support (e.g., `gcc`)
- A Unix-like operating system (Linux or macOS) or a Windows system with appropriate Pthreads support (e.g., using Cygwin or MinGW)

## License
This project is open-source and free to use for educational purposes.