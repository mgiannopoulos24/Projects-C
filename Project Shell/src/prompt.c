#include "headers.h"
#include <stdio.h>

void display_prompt() {
    printf("shell$ ");
}

int read_input(char *line) {
    if (fgets(line, MAX_INPUT, stdin) == NULL) {
        return 0;  // EOF or error
    }
    // Remove newline character if present
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
    return 1;
}
