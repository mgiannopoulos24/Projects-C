#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}
