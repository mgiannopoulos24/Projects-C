#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_PIPE "/tmp/jobExecutorServer_pipe"
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

void init_job_queue(JobQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

int is_queue_empty(JobQueue *queue) {
    return queue->front == queue->rear;
}

void enqueue_job(JobQueue *queue, Job *job) {
    if (queue->rear < 100) {
        queue->jobs[queue->rear] = job;
        queue->rear++;
    } else {
        printf("Job queue is full!\n");
    }
}

Job *dequeue_job(JobQueue *queue) {
    if (!is_queue_empty(queue)) {
        Job *job = queue->jobs[queue->front];
        queue->front++;
        return job;
    }
    return NULL;
}

void cleanup_queue(JobQueue *queue) {
    for (int i = queue->front; i < queue->rear; i++) {
        free(queue->jobs[i]);
    }
    queue->front = queue->rear = 0;
}

Job *parse_command(const char *command) {
    Job *job = (Job *)malloc(sizeof(Job));
    static int jobCounter = 1;

    snprintf(job->jobID, sizeof(job->jobID), "job_%d", jobCounter++);
    memset(job->command, 0, sizeof(job->command));

    // Create a mutable copy of the command
    char *cmd_copy = strdup(command);
    char *token;
    int i = 0;

    // Split the command string into tokens
    token = strtok(cmd_copy, " ");
    while (token != NULL && i < 9) {
        job->command[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");
    }
    job->command[i] = NULL;  // Null terminate the array for execvp
    free(cmd_copy);

    printf("Executing job: %s\n", job->command[0]);  // Debug print
    job->pid = 0;
    return job;
}

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

void execute_next_job() {
    if (!is_queue_empty(&jobQueue)) {
        Job *nextJob = dequeue_job(&jobQueue);
        execute_job(nextJob);
    }
}

void handle_stop_command(const char *jobID) {
    for (int i = jobQueue.front; i < jobQueue.rear; i++) {
        if (strcmp(jobQueue.jobs[i]->jobID, jobID) == 0) {
            free(jobQueue.jobs[i]);
            for (int j = i; j < jobQueue.rear - 1; j++) {
                jobQueue.jobs[j] = jobQueue.jobs[j + 1];
            }
            jobQueue.rear--;
            printf("%s removed\n", jobID);
            return;
        }
    }
    printf("Job %s not found in queue.\n", jobID);
}

void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        runningJobs--;
        printf("Job with PID %d completed.\n", pid);
        execute_next_job();
    }
}

void create_server_status_file() {
    FILE *file = fopen(SERVER_STATUS_FILE, "w");
    if (file == NULL) {
        perror("Failed to create server status file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", getpid());
    fclose(file);
}

void remove_server_status_file() {
    if (remove(SERVER_STATUS_FILE) != 0) {
        perror("Failed to remove server status file");
    }
}

int main() {
    signal(SIGCHLD, sigchld_handler);

    init_job_queue(&jobQueue);
    create_server_status_file();

    mkfifo(SERVER_PIPE, 0666);
    int pipe_fd = open(SERVER_PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("Failed to open server pipe");
        exit(EXIT_FAILURE);
    }

    char command[256];
    while (1) {
        memset(command, 0, sizeof(command));
        read(pipe_fd, command, sizeof(command));

        if (strncmp(command, "issueJob", 8) == 0) {
            const char *cmd = command + 9;  // Skip "issueJob " and point to actual command
            Job *newJob = parse_command(cmd);
            execute_job(newJob);
        } else if (strncmp(command, "setConcurrency", 14) == 0) {
            sscanf(command, "setConcurrency %d", &concurrency);
        } else if (strncmp(command, "stop", 4) == 0) {
            handle_stop_command(command + 5);
        } else if (strncmp(command, "exit", 4) == 0) {
            break;
        }
    }

    cleanup_queue(&jobQueue);
    // remove_server_status_file();
    close(pipe_fd);
    unlink(SERVER_PIPE);

    return 0;
}