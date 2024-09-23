#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int terms;
    double pi_approximation = 1.0; // Αρχική τιμή του γινομένου
    double term = sqrt(2);         // Πρώτος όρος: sqrt(2)

    // Έλεγχος αν έχει δοθεί το όρισμα γραμμής εντολών
    if (argc < 2) {
        printf("Enter the number of terms: ");
        if (scanf("%d", &terms) != 1 || terms < 1) {
            printf("Error: Number of terms must be a positive integer.\n");
            return 1;
        }
    } else {
        // Μετατροπή του ορίσματος από string σε ακέραιο
        terms = atoi(argv[1]);

        // Έλεγχος αν το όρισμα είναι έγκυρος αριθμός
        if (terms < 1) {
            printf("Error: Number of terms must be a positive integer.\n");
            return 1;
        }
    }

    // Υπολογισμός του γινομένου των όρων
    for (int i = 1; i <= terms; i++) {
        pi_approximation *= term / 2; // Ενημέρωση του γινομένου
        term = sqrt(2 + term);        // Ενημέρωση του όρου για την επόμενη επανάληψη
    }

    // Υπολογισμός της τελικής προσέγγισης του π
    double pi = 2 / pi_approximation;

    // Εκτύπωση του αποτελέσματος με 9 δεκαδικά ψηφία
    printf("Multiplied first %d terms, pi = %.9f\n", terms, pi);

    return 0;
}

// Μεταγλώττιση:
// gcc vieta.c -lm -o vieta
// Δοκιμές:
// ./vieta 2
// ./vieta 5
// ./vieta 50