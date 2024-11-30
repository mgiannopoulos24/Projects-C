#include "headers.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void execute_command(char **args, int num_args) {
    if (args[0] == NULL) {
        return; // No command entered
    }

    // Handle built-in commands
    if (handle_builtin(args)) {
        return;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("exec");
        }
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL);
    }
}
