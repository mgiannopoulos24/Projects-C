#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PIPE "/tmp/jobExecutorServer_pipe"

void send_command_to_server(const char *command) {
    int pipe_fd = open(SERVER_PIPE, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Failed to open server pipe");
        exit(EXIT_FAILURE);
    }
    write(pipe_fd, command, strlen(command));
    close(pipe_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: jobCommander <command>\n");
        return 1;
    }
    
    char command[256];
    snprintf(command, sizeof(command), "%s", argv[1]);
    send_command_to_server(command);
    
    if (strcmp(argv[1], "exit") == 0) {
        printf("Server terminated.\n");
    }

    return 0;
}
