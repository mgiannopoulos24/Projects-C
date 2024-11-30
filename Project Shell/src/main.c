#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char line[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        // Display prompt and read input
        display_prompt();
        if (!read_input(line)) {
            break;  // Handle EOF or error
        }

        // Parse input into arguments
        int num_args = parse_input(line, args);

        // Execute the command
        execute_command(args, num_args);
    }

    return 0;
}
