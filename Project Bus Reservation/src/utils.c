#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int get_int_input() {
    int input;
    scanf("%d", &input);
    clear_input_buffer();
    return input;
}

void clear_input_buffer() {
    while (getchar() != '\n');
}
