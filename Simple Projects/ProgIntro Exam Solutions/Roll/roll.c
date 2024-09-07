#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPONENT 31
#define MODULO 0x100000000  // 2^32

// Συνάρτηση για να ελέγξει αν τρεις αριθμοί είναι μια rickroll τριπλέτα
void check_rickroll_triplet(unsigned int a, unsigned int b, unsigned int c) {
    unsigned int pow2_i, pow2_j, pow2_k;
    unsigned int result;

    int found = 0;

    // Δοκιμάζουμε όλους τους δυνατούς συνδυασμούς I, J, K
    for (int i = 0; i <= MAX_EXPONENT; i++) {
        pow2_i = 1U << i; // Υπολογίζουμε 2^I
        for (int j = 0; j <= MAX_EXPONENT; j++) {
            if (i == j) continue; // I και J δεν πρέπει να είναι ίσα
            pow2_j = 1U << j; // Υπολογίζουμε 2^J
            for (int k = 0; k <= MAX_EXPONENT; k++) {
                if (k == i || k == j) continue; // K δεν πρέπει να είναι ίσο με I ή J
                pow2_k = 1U << k; // Υπολογίζουμε 2^K

                // Ελέγχουμε αν 2^I * a + 2^J * b = 2^K * c
                result = (pow2_i * a + pow2_j * b) % MODULO;
                if (result == (pow2_k * c) % MODULO) {
                    printf("Found rick-roll triplet: 2^%d * %u + 2^%d * %u = 2^%d * %u = %u\n",
                           i, a, j, b, k, c, result);
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("No rick-roll triplets found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return 1;
    }

    unsigned int a = (unsigned int)strtoul(argv[1], NULL, 10);
    unsigned int b = (unsigned int)strtoul(argv[2], NULL, 10);
    unsigned int c = (unsigned int)strtoul(argv[3], NULL, 10);

    check_rickroll_triplet(a, b, c);

    return 0;
}

// Μεταγλώττιση:
// gcc roll.c -o roll
// Δοκιμές:
// ./roll 17 42 101
// ./roll 17 42 100
// ./roll 3 5 7
// ./roll 0 0 1
