# Message Passing with Processes in C

This program is designed to simulate the concurrent generation and handling of messages by multiple processes. The program involves four child processes: three for generating messages and one for receiving and logging these messages.

### Components
1. Processes A, B, C: Generate random messages based on a given file and send them through pipes with a 30% probability at each iteration.
2. Process D: Receives the messages from the pipes and writes them to an output file.

### Directory Structure
- `outputs/`: Directory where the output files containing the logged messages are stored.

### How to compile
To compile the program, run the following command:

```bash
gcc -o message_handler message_handler.c -lpthread -lrt
```

### Usage
The program requires three command-line arguments:

`file`: Path to the file containing the lines to be used as messages.
`ct`: Sleep duration in milliseconds between attempts to send messages.
`N`: Number of iterations each message-generating process should perform.

```bash
./message_handler <file> <ct> <N>
```
Example:
```bash
User@Github:~$ ./message_handler messages.txt 500 10
Process A sent message: 7rffFlWohtHCJA4t7VHXlIyu8l8k5T
Process B sent message: prJLLtu2DjX4VbwSWvj3OPpcGWNsM0
Process C sent message: 0rZuLijtxGnbozoBToHAJfWBoWE29A
Process B sent message: RpxkV4rQIMftIsFTjWBx6ZfayU6MWk
Process C sent message: IXJpUHNXJrvKS5MYBhcDF7sD2f3Sci
Process C sent message: 1DVQPtK7LSRgu4UtR07Npy8YL0qmso
Process C sent message: sL8HnXfuW1Mjb6FFy7yINISzWWNrAv
User@Github:~$ The output with pid 3217 was saved in the outputs directory.
```
### How It Works
1. Initialization:

    - The program creates the outputs directory if it does not already exist.
    - Two semaphores are created: my_semaphore for coordinating the end of message generation and child_semaphore for signaling process completion.
2. Creating Pipes:
    - Three pipes are created for communication between the message-generating processes (A, B, C) and the message-handling process (D).
3. Forking Processes:
    - The program forks three child processes (A, B, C) for generating messages and one child process (D) for handling messages.
4. Message Generation (Processes A, B, C):
- Each message-generating process:
    - Generates a random message from the provided file.
    - Sends the message through its respective pipe with a 30% probability.
    - Sleeps for the specified duration (ct milliseconds) between iterations.
    - Signals completion using the semaphore.
5. Message Handling (Process D):
- The message-handling process:
    - Waits for the signals indicating that all message-generating processes have completed.
    - Reads messages from the pipes.
    - Logs the messages into an output file located in the outputs directory.
    - Signals completion using the semaphore.
6. Cleanup:
    - The parent process waits for all child processes to finish.
    - The semaphores are closed and unlinked.
### Notes
- Ensure that the input file containing messages (<file>) has a sufficient number of lines to avoid segmentation faults during random line selection.
- The outputs directory is created with permissions 0755. Ensure the parent directory is writable.
- The program uses semaphores to coordinate between processes, so proper cleanup of semaphores is essential to avoid resource leaks.
### Error Handling
- The program checks for errors at each critical step (e.g., file operations, semaphore operations, pipe operations) and reports them using perror.
- If an error occurs, the program exits with a non-zero status code.