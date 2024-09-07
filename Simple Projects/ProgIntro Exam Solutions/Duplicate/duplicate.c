#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 1000

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        // Αν δεν υπάρχουν ορίσματα, βγαίνουμε
        return 0;
    }

    char *args[MAX_ARGS];
    int counts[MAX_ARGS];
    int num_args = 0;
    int i, j;
    int found;

    // Επεξεργασία των ορισμάτων
    for (i = 1; i < argc; i++) {
        // Ψάχνουμε αν το τρέχον όρισμα υπάρχει ήδη στη λίστα
        found = 0;
        for (j = 0; j < num_args; j++) {
            if (strcmp(argv[i], args[j]) == 0) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        // Αν δεν βρέθηκε το όρισμα στη λίστα, το προσθέτουμε
        if (!found) {
            args[num_args] = argv[i];
            counts[num_args] = 1;
            num_args++;
        }
    }

    // Εκτύπωση των ορισμάτων που επαναλαμβάνονται
    for (i = 0; i < num_args; i++) {
        if (counts[i] > 1) {
            printf("dup: %s\n", args[i]);
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc duplicate.c -o duplicate
// Δοκιμές:
// ./duplicate foo bar foo baz bank zonk bazinga foo zonk