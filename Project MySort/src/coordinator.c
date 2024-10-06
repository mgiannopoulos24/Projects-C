#include "mysort.h"


void coordinator(const char *input_file, int k, const char *sort_exec1, const char *sort_exec2) {
    int i;
    int pipes[k][2];

    for (i = 0; i < k; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < k; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close(pipes[i][1]);
            // Pass the correct input file
            splitter_merger(input_file, k - i, (i % 2 == 0) ? sort_exec1 : sort_exec2);
            exit(EXIT_SUCCESS);
        } else {
            close(pipes[i][0]);
        }
    }

    for (i = 0; i < k; i++) {
        wait(NULL);
    }
}


void splitter_merger(const char *input_file, int k, const char *sort_exec) {
    int i;
    char output_file[32];

    // Fork processes to sort using sorter1 or sorter2
    for (i = 0; i < k; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // In child process

            // Create unique file names for output
            snprintf(output_file, sizeof(output_file), "./output_%d.bin", i);

            // Call sorter function with the given input file and the unique output file
            sorter(input_file, output_file, sort_exec);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to finish
    for (i = 0; i < k; i++) {
        wait(NULL);
    }
}

void sorter(const char *input_file, const char *output_file, const char *sort_exec) {
    // Execute the sorting program with input and output files as arguments
    execlp(sort_exec, sort_exec, input_file, output_file, (char *)NULL);

    // If execlp fails
    perror("execlp");
    exit(EXIT_FAILURE);
}