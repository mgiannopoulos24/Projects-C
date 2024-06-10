#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>
#include <sys/stat.h>

#define MSGSIZE 128
#define OUTPUT_DIR "outputs"

// Function to generate random message
char *generateRandomMessage(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Count number of lines
    int lineCount = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lineCount++;
        }
    }

    // Generate random line number
    int randomLine = rand() % lineCount;

    // Rewind file pointer
    rewind(file);

    // Find the randomly selected line
    char line[MSGSIZE];
    for (int i = 0; i < randomLine; i++) {
        fgets(line, MSGSIZE, file);
    }

    // Close file
    fclose(file);

    // Allocate memory for the message
    char *message = malloc(MSGSIZE);
    if (message == NULL) {
        perror("Error allocating memory for message");
        exit(EXIT_FAILURE);
    }

    // Copy the selected line to the message buffer
    strcpy(message, line);

    return message;
}

void my_sleep(long nanoseconds) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = nanoseconds;
    nanosleep(&ts, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <file> <ct> <N>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int ct = atoi(argv[2]);
    int N = atoi(argv[3]);

    // Create outputs directory if it doesn't exist
    mkdir(OUTPUT_DIR, 0755);

    // Delete existing semaphore
    sem_unlink("/my_semaphore");
    sem_unlink("/child_semaphore");

    // Create semaphore
    sem_t *sem;
    sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0644, 3); // Initialize with 3
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Create semaphore for controlling child processes
    sem_t *child_sem;
    child_sem = sem_open("/child_semaphore", O_CREAT | O_EXCL, 0644, 0);
    if (child_sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Create pipes
    int pipes[3][2];
    for (int i = 0; i < 3; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork processes A, B, C
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            // Close unused read end of pipe
            close(pipes[i][0]);

            // Generate and send messages
            srand(getpid());
            for (int j = 0; j < N; j++) {
                if ((double)rand() / RAND_MAX <= 0.3) { // 30% chance to send message
                    char *message = generateRandomMessage(filename);
                    write(pipes[i][1], message, strlen(message) + 1);
                    printf("Process %c sent message: %s", 'A' + i, message);
                    free(message);
                }
                my_sleep(ct);
            }

            // Close write end of pipe
            close(pipes[i][1]);
            sem_post(sem); // Signal that writing to pipe is done
            exit(EXIT_SUCCESS);
        }
    }

    // Fork process D
    pid_t pid_D = fork();
    if (pid_D == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_D == 0) { // Child process D
        // Close unused read ends of pipes
        for (int i = 0; i < 3; i++) {
            close(pipes[i][1]);
        }

        // Open file for writing messages
        char outfile_name[50];
        snprintf(outfile_name, sizeof(outfile_name), "%s/messages_%d.txt", OUTPUT_DIR, getpid());
        FILE *outfile = fopen(outfile_name, "w");
        if (outfile == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Wait for writing to pipes to finish
        for (int i = 0; i < 3; i++) {
            sem_wait(sem);
        }

        // Read messages from pipes and write to file
        char buf[MSGSIZE];
        int bytesRead;
        int openPipes = 3; // Track number of open pipes
        while (openPipes > 0) {
            for (int i = 0; i < 3; i++) {
                if (pipes[i][0] != -1) { // Check if pipe is open
                    bytesRead = read(pipes[i][0], buf, MSGSIZE);
                    if (bytesRead > 0) {
                        fprintf(outfile, "Process %c sent message: %s\n", 'A' + i, buf);
                    } else if (bytesRead == 0) { // Pipe closed
                        close(pipes[i][0]);
                        pipes[i][0] = -1; // Mark pipe as closed
                        openPipes--;
                    } else if (errno != EAGAIN && errno != EWOULDBLOCK) { // Error other than pipe empty
                        perror("read");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            my_sleep(ct);
        }

        // Close file
        fclose(outfile);
        printf("The output with pid %d was saved in the %s directory.\n", getpid(), OUTPUT_DIR);
        sem_close(sem);
        sem_close(child_sem);
        sem_unlink("/my_semaphore");
        sem_unlink("/child_semaphore");
        sem_post(child_sem); // Signal that this child process has finished
        exit(EXIT_SUCCESS);
    }

    // Close unused ends of pipes in parent process
    for (int i = 0; i < 3; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < 3; i++) {
        waitpid(-1, NULL, 0);
    }

    return 0;
}
