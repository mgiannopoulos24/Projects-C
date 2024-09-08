#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int main() {
    char line[MAX_LINE_LENGTH];
    int i;
    int first_word = 1;
    int in_first_word = 0;

    // Διαβάζουμε γραμμή προς γραμμή από την πρότυπη είσοδο
    while (fgets(line, sizeof(line), stdin)) {
        i = 0;

        // Επεξεργασία κάθε χαρακτήρα στη γραμμή
        while (line[i] != '\0') {
            if (line[i] == '\n') {
                // Εάν φτάσουμε στο τέλος της γραμμής, τυπώνουμε τον χαρακτήρα νέας γραμμής
                if (!first_word) {
                    printf("\033[0m"); // Τερματισμός bold μόλις ολοκληρωθεί η πρώτη λέξη
                }
                printf("\n");
                first_word = 1; // Επαναφορά της σημαίας για την επόμενη γραμμή
                break;
            } else if (isalpha(line[i])) {
                // Εάν είμαστε στην αρχή της πρώτης λέξης
                if (first_word) {
                    printf("\033[1m"); // Ξεκινάμε bold
                    first_word = 0;
                }
                // Εκτυπώνουμε το λατινικό γράμμα κανονικά
                printf("%c", line[i]);
                in_first_word = 1;
            } else {
                // Εάν δεν είμαστε πια στην πρώτη λέξη
                if (in_first_word) {
                    printf("\033[0m"); // Τερματισμός bold
                    in_first_word = 0;
                }
                // Εάν ο χαρακτήρας δεν είναι λατινικό γράμμα, τυπώνουμε κενό
                printf(" ");
            }
            i++;
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc bold.c -o bold
// Δοκιμή:
// ./bold < island.txt