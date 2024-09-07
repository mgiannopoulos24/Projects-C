#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Συνάρτηση για τον υπολογισμό του μέγιστου κοινού διαιρέτη (ΜΚΔ) με χρήση του αλγορίθμου του Ευκλείδη
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive integer1> <positive integer2>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long num1 = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || num1 <= 0) {
        fprintf(stderr, "Numbers must be positive\n");
        return 1;
    }

    long num2 = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || num2 <= 0) {
        fprintf(stderr, "Numbers must be positive\n");
        return 1;
    }

    unsigned long long u_num1 = (unsigned long long)num1;
    unsigned long long u_num2 = (unsigned long long)num2;

    unsigned long long result = gcd(u_num1, u_num2);
    printf("Greatest common divisor of %llu and %llu is %llu\n", u_num1, u_num2, result);

    return 0;
}

// Μεταγλώττιση:
// gcc gcd.c -o gcd
// Δοκιμές:
// ./gcd 42 27
// ./gcd 42 -27
// ./gcd 54 24
// ./gcd 9827345 9182767
// ./gcd 782936492674398272 982137984792892
// ./gcd 260056890954482 23809214813964