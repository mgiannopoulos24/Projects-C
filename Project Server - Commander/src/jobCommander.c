#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_PIPE "/tmp/jobExecutorServer_pipe"
#define SERVER_STATUS_FILE "jobExecutorServer.txt"

void start_server() {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        execlp("./build/jobExecutorServer", "./build/jobExecutorServer", NULL);
        perror("Failed to start jobExecutorServer");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {  // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    sleep(1); // Allow time for the server to initialize
}

void check_and_start_server() {
    if (access(SERVER_STATUS_FILE, F_OK) == -1) {
        printf("Server not running. Starting server...\n");
        start_server();
    }
}

void send_command_to_server(const char *command) {
    int pipe_fd = open(SERVER_PIPE, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Failed to open server pipe");
        exit(EXIT_FAILURE);
    }

    size_t remaining = strlen(command);
    const char *current = command;
    size_t chunk_size = 4096;  // Use a larger buffer size

    while (remaining > 0) {
        size_t to_write = (remaining < chunk_size) ? remaining : chunk_size;
        ssize_t written = write(pipe_fd, current, to_write);

        if (written == -1) {
            perror("Failed to write to server pipe");
            close(pipe_fd);
            exit(EXIT_FAILURE);
        }

        current += written;
        remaining -= written;
    }

    close(pipe_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: jobCommander <command>\n");
        return 1;
    }

    check_and_start_server();

    // Calculate the total length of the command
    size_t command_size = 0;
    for (int i = 1; i < argc; i++) {
        command_size += strlen(argv[i]) + 1;  // Account for spaces/null terminators
    }

    // Allocate sufficient memory
    char *command = malloc(command_size + 1);  // +1 for the final null terminator
    if (command == NULL) {
        perror("Failed to allocate command buffer");
        return 1;
    }

    // Construct the full command string
    command[0] = '\0';  // Initialize as an empty string
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) {
            strcat(command, " ");
        }
    }

    printf("Sending command: %s\n", command);  // Debugging

    // Send the command to the server
    send_command_to_server(command);
    free(command);

    if (strcmp(argv[1], "exit") == 0) {
        printf("Server terminated.\n");
    }

    return 0;
}