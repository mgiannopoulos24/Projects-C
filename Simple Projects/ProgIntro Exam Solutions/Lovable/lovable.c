#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h> // Include this header for PRIu64

// Συνάρτηση που ελέγχει αν ένας αριθμός είναι παλινδρομικός
int is_palindrome(uint64_t num) {
    char str[21]; // Μπορεί να αποθηκεύσει μέχρι και αριθμούς μεγέθους 10^18
    sprintf(str, "%" PRIu64, num); // Μετατρέπουμε τον αριθμό σε συμβολοσειρά
    int len = strlen(str);
    
    // Ελέγχουμε αν η συμβολοσειρά είναι παλινδρομική
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// Συνάρτηση που ελέγχει αν ένας αριθμός είναι τέλειος κύβος
int is_perfect_cube(uint64_t num) {
    uint64_t cube_root = round(cbrt(num)); // Υπολογίζουμε τη ρίζα κύβου του αριθμού
    return (cube_root * cube_root * cube_root == num);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return 1;
    }

    uint64_t start = strtoull(argv[1], NULL, 10);
    uint64_t end = strtoull(argv[2], NULL, 10);

    // Βρίσκουμε τον ελάχιστο και μέγιστο ακέραιο που ο κύβος του εμπίπτει στο εύρος
    uint64_t min_cube_root = ceil(cbrt(start));
    uint64_t max_cube_root = floor(cbrt(end));

    // Εξετάζουμε κάθε τέλειο κύβο στο εύρος
    for (uint64_t i = min_cube_root; i <= max_cube_root; i++) {
        uint64_t cube = i * i * i;

        if (is_palindrome(cube)) {
            printf("%" PRIu64 "\n", cube);
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc lovable.c -o lovable -lm
// Δοκιμές:
// ./lovable 1 1000000
// ./lovable 1000000 1000000000
// ./lovable 1000000000 1000000000000