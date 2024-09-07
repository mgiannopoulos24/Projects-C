#include <stdio.h>
#include <stdlib.h>

// Συνάρτηση που ελέγχει αν ένας αριθμός έχει άρτια παρτίδα
int has_even_parity(unsigned long long number) {
    int count = 0;
    // Μετράμε τα bits που είναι 1
    while (number > 0) {
        count += number & 1;
        number >>= 1;
    }
    // Επιστρέφουμε αν ο αριθμός των bits που είναι 1 είναι άρτιος
    return count % 2 == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        char *endptr;
        unsigned long long number = strtoull(argv[i], &endptr, 10);

        if (*endptr != '\0') {
            fprintf(stderr, "Invalid number: %s\n", argv[i]);
            continue;
        }

        if (has_even_parity(number)) {
            printf("Number %llu has even parity\n", number);
        } else {
            printf("Number %llu does not have even parity\n", number);
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc parity.c -o parity
// Δοκιμές:
// ./parity 5 7 64 65 987234 97823462
// ./parity 92873847981279843
// ./parity 92873847981279844