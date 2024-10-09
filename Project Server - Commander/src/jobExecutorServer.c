#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define SERVER_PIPE "jobExecutorServer.txt"
#define SERVER_STATUS_FILE "jobExecutorServer.txt"

// Job structure definition
typedef struct {
    char jobID[16];
    char *command[10];
    int pid;
} Job;

// Job queue structure
typedef struct {
    Job *jobs[100];
    int front, rear;
} JobQueue;

JobQueue jobQueue;
int concurrency = 1;  // Default concurrency level
int runningJobs = 0;

// Forward declaration of execute_next_job to avoid implicit declaration warning
void execute_next_job();

// Initialize the job queue
void init_job_queue(JobQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

// Check if the queue is empty
int is_queue_empty(JobQueue *queue) {
    return queue->front == queue->rear;
}

// Enqueue a job into the job queue
void enqueue_job(JobQueue *queue, Job *job) {
    if (queue->rear < 100) {
        queue->jobs[queue->rear] = job;
        queue->rear++;
    } else {
        printf("Job queue is full!\n");
    }
}

// Dequeue a job from the job queue
Job *dequeue_job(JobQueue *queue) {
    if (!is_queue_empty(queue)) {
        Job *job = queue->jobs[queue->front];
        queue->front++;
        return job;
    }
    return NULL;
}

// Cleanup the job queue
void cleanup_queue(JobQueue *queue) {
    for (int i = queue->front; i < queue->rear; i++) {
        free(queue->jobs[i]);
    }
    queue->front = queue->rear = 0;
}

// Read command from the named pipe
void read_from_pipe(char *buffer) {
    int pipe_fd = open(SERVER_PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("Error opening pipe for reading");
        exit(EXIT_FAILURE);
    }
    read(pipe_fd, buffer, 256);
    close(pipe_fd);
}

Job *parse_command(const char *command) {
    Job *job = (Job *)malloc(sizeof(Job));
    snprintf(job->jobID, sizeof(job->jobID), "job_%d", rand() % 100);  // Example jobID generation

    char *token;
    int i = 0;
    char *cmd_copy = strdup(command);  // Make a copy of the command to avoid modifying the original

    token = strtok(cmd_copy, " ");
    while (token != NULL) {
        job->command[i] = strdup(token);  // Store each argument
        i++;
        token = strtok(NULL, " ");
    }
    job->command[i] = NULL;  // Terminate the argument list
    free(cmd_copy);

    job->pid = 0;  // PID is 0 until the job is executed
    return job;
}

// SIGCHLD handler for completed jobs
void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        runningJobs--;
        printf("Job with PID %d completed.\n", pid);
        execute_next_job(); // Executes the next job in the queue if possible
    }
}

// Function to execute a job
void execute_job(Job *job) {
    if (runningJobs < concurrency) {
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            execvp(job->command[0], job->command);
            perror("exec failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {  // Parent process
            runningJobs++;
            job->pid = pid;
            printf("Job %s started with PID %d\n", job->jobID, pid);
        } else {
            perror("fork failed");
        }
    } else {
        enqueue_job(&jobQueue, job);
    }
}

// Function to execute the next job in the queue
void execute_next_job() {
    if (!is_queue_empty(&jobQueue)) {
        Job *nextJob = dequeue_job(&jobQueue);
        execute_job(nextJob);
    }
}

// Create server status file
void create_server_status_file() {
    FILE *file = fopen(SERVER_STATUS_FILE, "w");
    if (file == NULL) {
        perror("Failed to create server status file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", getpid());
    fclose(file);
}

// Remove server status file
void remove_server_status_file() {
    if (remove(SERVER_STATUS_FILE) != 0) {
        perror("Failed to remove server status file");
    }
}

int main() {
    signal(SIGCHLD, sigchld_handler);

    init_job_queue(&jobQueue);
    create_server_status_file();

    while (1) {
        // Read commands from the named pipe and handle them
        char command[256];
        read_from_pipe(command);

        if (strncmp(command, "issueJob", 8) == 0) {
            Job *newJob = parse_command(command + 9);  // Skip the "issueJob" part
            execute_job(newJob);
        } else if (strncmp(command, "setConcurrency", 14) == 0) {
            sscanf(command, "setConcurrency %d", &concurrency);
        } else if (strncmp(command, "stop", 4) == 0) {
            // Handle stop command
        } else if (strncmp(command, "exit", 4) == 0) {
            break;
        }
    }

    cleanup_queue(&jobQueue);
    remove_server_status_file();
    return 0;
}