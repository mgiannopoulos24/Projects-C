#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("chdir");
            }
        }
        return 1; // Handled as a built-in command
    }
    return 0; // Not a built-in command
}
