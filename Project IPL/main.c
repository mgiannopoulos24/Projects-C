#include "parser.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check for correct number of arguments, expecting at least one argument (the IPL program file)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ipl_program_file>\n", argv[0]);
        return 1;
    }


    return 0;
}
