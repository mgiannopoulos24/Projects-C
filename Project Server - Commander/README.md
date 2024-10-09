# Project Job Executor

## Overview
The **Job Executor Project** is a system programming project for managing and executing multiple jobs, developed as part of the Κ24 System Programming course (Spring 2024). The project involves two main components: **jobCommander** and **jobExecutorServer**, which work together to provide an interface for executing, managing, and controlling multiple tasks concurrently.

The key components include:
1. **jobCommander**: A command-line utility through which users can submit jobs, adjust concurrency levels, stop jobs, and poll the server for information.
2. **jobExecutorServer**: A server responsible for managing the execution of jobs, handling concurrency, and responding to commands from jobCommander.
3. **Bash Scripts**: Additional shell scripts ("multijob.sh" and "allJobsStop.sh") for more advanced management capabilities.

## Structure
- **build/**: Contains compiled executables for `jobCommander`, `jobExecutorServer`, and other utilities.
- **include/**: Contains header files for the project (if applicable).
- **obj/**: Object files generated during compilation.
- **scripts/**: Includes bash scripts for stopping and submitting multiple jobs.
  - **allJobsStop.sh**: Stops all currently running and queued jobs.
  - **multijob.sh**: Reads job commands from multiple input files and issues them to the jobExecutorServer.
- **src/**: Source code files.
  - **jobCommander.c**: Implements the interface for interacting with the jobExecutorServer.
  - **jobExecutorServer.c**: Implements the main server responsible for job execution.
  - **progDelay.c**: Utility to simulate a delay, used as a sample job.
- **tests/**: Contains test commands and scripts to validate project functionality.
- **Makefile**: A Makefile to compile the source code and generate the executables.

## Components Details

### jobCommander
The `jobCommander` provides the main interface for interacting with the jobExecutor system. The user can perform the following actions using command-line arguments:
- **issueJob <job>**: Submits a job for execution. The jobExecutorServer assigns a unique job ID and queue position.
- **setConcurrency <N>**: Sets the maximum number of jobs that can be run concurrently.
- **stop <jobID>**: Stops the specified job if it is currently running or removes it from the queue.
- **poll [running, queued]**: Displays information about currently running or queued jobs.
- **exit**: Terminates the jobExecutorServer.

The communication between `jobCommander` and `jobExecutorServer` is handled using **named pipes**.

### jobExecutorServer
The `jobExecutorServer` is the core of the project, managing the lifecycle of jobs and maintaining concurrency as specified. The server:
- Accepts job commands via a named pipe.
- Maintains a **job queue** to manage submitted jobs.
- Executes jobs with respect to the **concurrency limit**, using `fork()` and `execvp()` system calls.
- Handles **child process completion** via the `SIGCHLD` signal, allowing the server to start new jobs from the queue as running jobs complete.

### progDelay Utility
The `progDelay` program simulates a delay for demonstration purposes. It accepts an argument specifying the duration and prints a character for each second of delay.

### Bash Scripts
- **multijob.sh**: Reads job commands from multiple files and submits them sequentially using `jobCommander`.
- **allJobsStop.sh**: Stops all running and queued jobs using `jobCommander` commands to poll and terminate the jobs.

## Compilation and Execution
### Compilation
To compile the project, run the following command from the root directory:
```sh
make
```
This will create the executables `jobCommander` and `jobExecutorServer` in the `build/` directory.

### Running the Project
Before running the project, you need to create the necessary files and pipes:
```sh
touch jobExecutorServer.txt
mkfifo /tmp/jobExecutorServer_pipe
```

1. Start the `jobExecutorServer`:
```sh
./build/jobExecutorServer
```
2. Use `jobCommander` to submit jobs and manage the server. For example:
```sh
./build/jobCommander issueJob "ls -l /path/to/directory"
./build/jobCommander setConcurrency 4
./build/jobCommander poll running
./build/jobCommander stop job_1
./build/jobCommander exit
```

### Bash Scripts
- To submit jobs from multiple files:
```sh
./scripts/multijob.sh file1.txt file2.txt
```
- To stop all jobs:
```sh
./scripts/allJobsStop.sh
```

## Design Considerations
- The **job queue** uses a simple array structure to manage jobs, and each job is assigned a **unique identifier** (`job_XX`) to facilitate tracking and management.
- **Named pipes** are used for communication between `jobCommander` and `jobExecutorServer` to facilitate asynchronous command passing.
- **Concurrency control** is implemented to manage the number of concurrently running jobs, adapting dynamically when the limit changes.
- **Signal handling** (`SIGCHLD`) is used to manage child process terminations and start queued jobs without manual intervention.

## Additional Notes
- The project uses **separate compilation** and is compiled using the provided **Makefile**.
- The source code adheres to good software engineering practices, with emphasis on **modularity**, **readability**, and **documentation**.

