#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Συνάρτηση που ελέγχει αν δύο αριθμοί είναι μαγικό ζευγάρι
int are_magic_pair(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return 0; // Διαφορετικό μήκος, δεν είναι μαγικό ζευγάρι
    }

    // Δημιουργία και ταξινόμηση των ψηφίων για τον πρώτο αριθμό
    char *sorted1 = malloc(len1 + 1);
    char *sorted2 = malloc(len2 + 1);
    if (!sorted1 || !sorted2) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(sorted1, str1);
    strcpy(sorted2, str2);

    // Ταξινόμηση των ψηφίων
    qsort(sorted1, len1, sizeof(char), (int (*)(const void*, const void*)) strcmp);
    qsort(sorted2, len2, sizeof(char), (int (*)(const void*, const void*)) strcmp);

    // Σύγκριση των ταξινομημένων ψηφίων
    int result = strcmp(sorted1, sorted2) == 0;

    free(sorted1);
    free(sorted2);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }

    // Ελέγχουμε αν τα ορίσματα είναι αριθμοί και θετικοί
    char *endptr;
    long num1 = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || num1 <= 0) {
        printf("Not a magic pair\n");
        return 1;
    }

    long num2 = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || num2 <= 0) {
        printf("Not a magic pair\n");
        return 1;
    }

    // Μετατρέπουμε τους αριθμούς σε strings
    char str1[32], str2[32];
    snprintf(str1, sizeof(str1), "%ld", num1);
    snprintf(str2, sizeof(str2), "%ld", num2);

    if (are_magic_pair(str1, str2)) {
        printf("%ld and %ld are a magic pair.\n", num1, num2);
    } else {
        printf("Not a magic pair\n");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc magicpair.c -o magicpair
// Δοκιμές:
// ./magicpair 1980 1908
// ./magicpair 1980 198
// ./magicpair -18 -18
// ./magicpair 4321 1234
// ./magicpair 4231444232 3244214243