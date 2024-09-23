#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Συνάρτηση για τον έλεγχο αν ο αριθμός είναι τυχερός
int is_lucky(long long n, long long *i_result, long long *j_result) {
    // Δοκιμάζουμε όλες τις τιμές του i, ξεκινώντας από το 1 μέχρι το n^(1/3)
    for (long long i = 1; i <= cbrt(n); i++) {
        long long i_cubed = i * i * i;  // Υπολογισμός του i^3

        // Υπολογισμός του j^3 = n - i^3
        long long j_cubed = n - i_cubed;
        if (j_cubed <= 0) continue;  // Αγνοούμε αρνητικές τιμές

        // Υπολογίζουμε το j ως την κυβική ρίζα του j^3
        long long j = cbrt(j_cubed);

        // Αν το j^3 είναι ίσο με το υπόλοιπο, τότε βρήκαμε λύση
        if (j * j * j == j_cubed) {
            *i_result = i;
            *j_result = j;
            return 1;  // Ο αριθμός είναι τυχερός
        }
    }

    return 0;  // Δεν βρέθηκε καμία λύση, ο αριθμός δεν είναι τυχερός
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide at least one integer as argument.\n");
        return 1;
    }

    // Ελέγχουμε κάθε όρισμα που δίνεται στη γραμμή εντολών
    for (int arg = 1; arg < argc; arg++) {
        long long number = atoll(argv[arg]);  // Μετατροπή από string σε long long

        long long i, j;  // Μεταβλητές για τα αποτελέσματα του i και j

        // Έλεγχος αν ο αριθμός είναι τυχερός
        if (is_lucky(number, &i, &j)) {
            printf("%lld is lucky: %lld^3 + %lld^3 = %lld\n", number, i, j, number);
        } else {
            printf("No positive i, j exist such that i^3+j^3 = %lld\n", number);
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc lucky.c -o lucky -lm
// Δοκιμές:
// ./lucky 28 95 128 298374 508167898112