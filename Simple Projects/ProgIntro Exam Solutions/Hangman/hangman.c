#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 1000

// Συνάρτηση που ελέγχει αν μια λέξη ταιριάζει με το μοτίβο
int match_pattern(const char *word, const char *pattern) {
    // Έλεγχος αν τα μήκη των λέξεων ταιριάζουν
    if (strlen(word) != strlen(pattern)) {
        return 0;
    }

    // Έλεγχος κάθε χαρακτήρα
    for (size_t i = 0; i < strlen(pattern); i++) {
        if (pattern[i] == '_') {
            // Το γράμμα δεν έχει αποκαλυφθεί, συνεχίζουμε
            continue;
        } else {
            // Συγκρίνουμε τα γράμματα ανεξαρτήτως πεζών-κεφαλαίων
            if (tolower((unsigned char)word[i]) != tolower((unsigned char)pattern[i])) {
                return 0; // Δεν ταιριάζει το γράμμα
            }
        }
    }
    return 1; // Η λέξη ταιριάζει με το μοτίβο
}

int main(int argc, char *argv[]) {
    // Έλεγχος ορισμάτων
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word_file> <pattern>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *pattern = argv[2];

    // Άνοιγμα του αρχείου λέξεων
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'.\n", filename);
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    int found = 0; // Μεταβλητή που δείχνει αν βρέθηκε τουλάχιστον μία λέξη

    // Διαβάζουμε κάθε λέξη από το αρχείο
    while (fgets(word, sizeof(word), file)) {
        // Αφαίρεση χαρακτήρων νέας γραμμής και carriage return
        word[strcspn(word, "\r\n")] = '\0';

        // Παραλείπουμε κενές γραμμές
        if (strlen(word) == 0) {
            continue;
        }

        // Έλεγχος αν η λέξη ταιριάζει με το μοτίβο
        if (match_pattern(word, pattern)) {
            printf("%s\n", word);
            found = 1;
        }
    }

    fclose(file);

    // Αν δεν βρέθηκε καμία λέξη
    if (!found) {
        printf("No words matching guess found\n");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc hangman.c -o hangman
// Δοκιμές:
// ./hangman words.txt t_____
// ./hangman words.txt __r___
// ./hangman words.txt ___
// ./hangman words.txt d__
// ./hangman words.txt _e_e__
