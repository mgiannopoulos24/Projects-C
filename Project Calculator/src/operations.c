#include <stdio.h>
#include <math.h>
#include "operations.h"

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

double power(double base, double exp) {
    return pow(base, exp);
}

double square_root(double a) {
    return sqrt(a);
}

int modulus(int a, int b) {
    return a % b;
}

double sine(double a) {
    return sin(a);
}

double cosine(double a) {
    return cos(a);
}

double tangent(double a) {
    return tan(a);
}
