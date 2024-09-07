#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Μέγιστο μήκος γραμμής
#define MAX_LINE_LENGTH 1024

int main() {
    char line[MAX_LINE_LENGTH];

    // Διαβάζουμε κάθε γραμμή από την πρότυπη είσοδο
    while (fgets(line, sizeof(line), stdin)) {
        // Αφαιρούμε το newline στο τέλος της γραμμής αν υπάρχει
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Εκτυπώνουμε τη γραμμή αντίστροφα
        for (ssize_t i = len - 1; i >= 0; i--) {
            putchar(line[i]);
        }
        putchar('\n'); // Εκτύπωση νέας γραμμής
    }

    return 0;
}

// Μεταγλώττιση:
// gcc flip.c -o flip
// Δοκιμές:
// ./flip < riddle.txt