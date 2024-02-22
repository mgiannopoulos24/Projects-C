#include "executor.h"
#include <stdio.h>

void execute_command(const Command cmd) {
    printf("Executing command: %s\n", cmd.command);
}
