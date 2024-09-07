#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Συνάρτηση για να βρει το μέγιστο μήκος γραμμής
int find_max_line_length(FILE *file) {
    char line[MAX_LINE_LENGTH];
    int max_length = 0;

    // Ξαναγυρνάμε στην αρχή του αρχείου
    fseek(file, 0, SEEK_SET);

    // Διαβάζουμε κάθε γραμμή και βρίσκουμε το μέγιστο μήκος
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (line[length - 1] == '\n') {
            length--;  // Αφαιρούμε το χαρακτήρα νέας γραμμής
        }
        if (length > max_length) {
            max_length = length;
        }
    }

    return max_length;
}

int main() {
    char line[MAX_LINE_LENGTH];
    int max_length;
    FILE *file = stdin;  // Διαβάζουμε από την πρότυπη είσοδο

    // Βρίσκουμε το μέγιστο μήκος γραμμής
    max_length = find_max_line_length(file);

    // Εκτυπώνουμε την πρώτη γραμμή του κάδρου
    for (int i = 0; i < max_length + 4; i++) {
        putchar('*');
    }
    putchar('\n');

    // Ξαναγυρνάμε στην αρχή του αρχείου
    fseek(file, 0, SEEK_SET);
    
    // Εκτυπώνουμε το κείμενο μέσα στο κάδρο
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (line[length - 1] == '\n') {
            line[length - 1] = '\0';  // Αφαιρούμε το χαρακτήρα νέας γραμμής
            length--;
        }
        // Εκτύπωση γραμμής μέσα στο κάδρο
        printf("* %s%*s*\n", line, max_length - length + 1, "");
    }

    // Εκτυπώνουμε την τελευταία γραμμή του κάδρου
    for (int i = 0; i < max_length + 4; i++) {
        putchar('*');
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc frame.c -o frame
// Δοκιμή:
// ./frame < message.txt