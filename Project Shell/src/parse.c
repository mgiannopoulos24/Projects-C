#include "headers.h"
#include <string.h>
#include <stdlib.h>

int parse_input(char *line, char **args) {
    int i = 0;
    char *token = strtok(line, " ");
    
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the argument list
    return i;
}
