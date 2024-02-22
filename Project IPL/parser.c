#include "parser.h"
#include <string.h>
#include <stdlib.h> // For malloc

char* strdup(const char* s) {
    char* newStr = malloc(strlen(s) + 1); // +1 for the null terminator
    if (newStr) {
        strcpy(newStr, s);
    }
    return newStr;
}

Command parse_line(const char *line) {
    Command cmd;
    cmd.command = strdup(line); 
    return cmd;
}
