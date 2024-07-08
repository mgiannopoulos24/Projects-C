# Scheduling Algorithms

This project implements various CPU scheduling algorithms in C. Each program reads a list of tasks from a file, schedules them based on specific algorithms, and simulates their execution on a CPU.

## Algorithms Implemented

1. First-Come, First-Served (FCFS)
2. Shortest Remaining Time First (SRTF)
3. Priority Round Robin
4. Monotonic
5. Earliest Deadline First (EDF)

## Files

- schedule_fcfs.c: Implements the FCFS scheduling algorithm.
- schedule_srtf.c: Implements the SRTF scheduling algorithm.
- schedule_priority_rr.c: Implements the Priority Round Robin scheduling algorithm.
- schedule_monotonic.c: Implements the Monotonic scheduling algorithm.
- schedule_edf.c: Implements the EDF scheduling algorithm.
- list.c: Provides functions for managing a linked list of tasks.
- CPU.c: Simulates the CPU execution.

### Compilation

- All together:
    - `make all`

- One at a time:
    - `make fcfs`
    - `make srtf`
    - `make priority_rr`
    - `make monotonic`
    - `make edf`

### Execution

1. FCFS: 
```bash 
cd bin/
./fcfs ../schedules/fcfs-schedule.txt
```
2. SRTF:
```bash
cd bin/
./srtf ../schedules/srtf-schedule.txt 
```
3. Priority Round Robin:
```bash
cd bin/
./priority_rr ../schedules/priority-schedule.txt
```
4. Monotonic:
```bash
cd bin/
./monotonic ../schedules/monotonic-schedule.txt
```
5. EDF:
```bash
cd bin/
./edf ../schedules/edf-schedule.txt
```

### Example run

1. FCFS:
```bash
User@Github:~$ ./fcfs ../schedules/fcfs-schedule.txt 
read [P1] [0] [1] [24] [0]
read [P2] [1] [1] [3] [0]
read [P3] [2] [1] [3] [0]
Scheduling tasks using FCFS...
Running task P1 for 24 time units.
Running task P2 for 3 time units.
Running task P3 for 3 time units.
```
2. SRTF:
```bash
User@Github:~$ ./srtf ../schedules/srtf-schedule.txt
read [P1] [0] [1] [6] [20]
read [P2] [1] [1] [7] [15]
read [P3] [2] [2] [5] [10]
read [P4] [3] [3] [8] [25]
Scheduling tasks using SRTF...
Running task P3 for 5 time units.
Running task P1 for 6 time units.
Running task P2 for 7 time units.
Running task P4 for 8 time units.
```
3. Priority Round Robin:
```bash
User@Github:~$ ./priority_rr ../schedules/priority-schedule.txt 
read [P1] [0] [2] [8]
read [P2] [1] [1] [5]
read [P3] [2] [3] [6]
read [P4] [3] [2] [7]
Scheduling tasks using Priority RR...
Running task P1 for 4 time units.
Running task P2 for 4 time units.
Running task P3 for 4 time units.
Running task P4 for 4 time units.
Running task P1 for 4 time units.
Running task P2 for 1 time units.
Running task P3 for 2 time units.
Running task P4 for 3 time units.
```
4. Monotonic:
```bash
User@Github:~$ ./monotonic ../schedules/monotonic-schedule.txt 
read [P1] [0] [3] [8] [12]
read [P2] [1] [2] [5] [10]
read [P3] [2] [1] [6] [15]
read [P4] [3] [2] [4] [8]
read [P5] [4] [3] [7] [12]
Scheduling tasks using Rate Monotonic...
Running task P1 for 8 time units.
Running task P2 for 5 time units.
Running task P3 for 6 time units.
Running task P4 for 4 time units.
Running task P5 for 7 time units.
```
5. EDF:
```bash
User@Github:~$ ./edf ../schedules/edf-schedule.txt 
read [P1] [0] [1] [10] [15]
read [P2] [1] [2] [5] [10]
read [P3] [2] [3] [8] [20]
read [P4] [3] [4] [3] [6]
read [P5] [4] [5] [6] [12]
Scheduling tasks using Earliest Deadline First (EDF)...
Running task P4 for 3 time units.
Missed deadline for task P2
Running task P5 for 6 time units.
Missed deadline for task P1
Running task P3 for 8 time units.
```

### Cleaning
To remove compiled binaries and object files, run:

`make clean`

**Note:** This project is an assignment of the 3rd series of exercises of the Operating Systems (17.122) course of DIND NKUA.