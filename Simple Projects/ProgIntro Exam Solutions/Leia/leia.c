#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Συνάρτηση για έλεγχο αν ένας αριθμός είναι πρώτος
bool is_prime(unsigned long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (unsigned long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Συνάρτηση για τον υπολογισμό των δίδυμων πρώτων
int count_twin_primes(unsigned long start, unsigned long end) {
    int count = 0;
    for (unsigned long i = start; i <= end - 2; i++) {
        if (is_prime(i) && is_prime(i + 2)) {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return 1;
    }

    unsigned long start = strtoul(argv[1], NULL, 10);
    unsigned long end = strtoul(argv[2], NULL, 10);

    // Έλεγχος εγκυρότητας των ορίων
    if (start > end || start < 0 || end < 0) {
        fprintf(stderr, "Invalid range.\n");
        return 1;
    }

    int result = count_twin_primes(start, end);
    printf("%d\n", result);

    return 0;
}


// Μεταγλώττιση:
// gcc leia.c -o leia
// Εκτέλεση:
// ./leia 1 10
// ./leia 10 100
// ./leia 1 10000000
// ./leia 100000000000 100000100000