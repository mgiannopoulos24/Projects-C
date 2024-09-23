#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 1000000 // Μέγιστο όριο για τους αριθμούς

// Συνάρτηση που υπολογίζει το F(n) = n + άθροισμα των ψηφίων του n
int F(int n) {
    int sum = n;
    while (n > 0) {
        sum += n % 10; // Προσθέτουμε το τελευταίο ψηφίο
        n /= 10;       // Αφαιρούμε το τελευταίο ψηφίο
    }
    return sum;
}

int main(int argc, char *argv[]) {
    // Έλεγχος ότι έχουν δοθεί ακριβώς δύο ορίσματα (low και high)
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <low> <high>\n", argv[0]);
        return 1;
    }

    // Μετατροπή των ορισμάτων σε ακέραιους
    int low = atoi(argv[1]);
    int high = atoi(argv[2]);

    // Έλεγχος εγκυρότητας των τιμών
    if (low > high || low < 1 || high >= MAX_LIMIT) {
        fprintf(stderr, "Error: Invalid range. Ensure that 1 <= low <= high < %d.\n", MAX_LIMIT);
        return 1;
    }

    // Πίνακας για την επισήμανση των μη εαυτών αριθμών
    int *is_self = (int *)calloc(high + 1000, sizeof(int));
    if (is_self == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    // Υπολογισμός των F(m) για m από 1 έως high
    for (int m = 1; m <= high; m++) {
        int generated = F(m);
        if (generated <= high + 1000) {
            is_self[generated] = 1; // Σημειώνουμε ότι ο αριθμός generated δεν είναι εαυτός αριθμός
        }
    }

    // Εκτύπωση των εαυτών αριθμών στο εύρος [low, high]
    printf("Self numbers:");
    int count = 0;
    for (int n = low; n <= high; n++) {
        if (is_self[n] == 0) {
            printf(" %d", n);
            count++;
        }
    }
    printf("\nFound %d total\n", count);

    // Απελευθέρωση μνήμης
    free(is_self);

    return 0;
}


// Μεταγλώττιση:
// gcc self.c -o self
// Δοκιμές:
// ./self 9900 10000