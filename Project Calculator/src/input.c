#include <stdio.h>
#include "input.h"

char get_operator() {
    char operator[10];
    scanf("%s", operator);

    // Simplified operator interpretation
    if (operator[0] == 's' && operator[1] == 'i') return 's';
    if (operator[0] == 'c' && operator[1] == 'o') return 'c';
    if (operator[0] == 't' && operator[1] == 'a') return 't';
    if (operator[0] == 's' && operator[1] == 'q') return 'r';
    return operator[0];
}

void get_operands(double *a, double *b) {
    scanf("%lf %lf", a, b);
}

void get_operand(double *a) {
    scanf("%lf", a);
}
