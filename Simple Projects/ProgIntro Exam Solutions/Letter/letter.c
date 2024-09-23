#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

// Συνάρτηση για την αφαίρεση κενών διαστημάτων από την αρχή και το τέλος
void trim(char *str) {
    char *end;

    // Αφαίρεση κενών από την αρχή
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // Όλα κενά
        return;

    // Αφαίρεση κενών από το τέλος
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Τοποθέτηση του τερματικού χαρακτήρα
    *(end+1) = '\0';
}

int main() {
    // Δήλωση μεταβλητών
    char word[MAX_WORD_LENGTH] = {0}; // Η λέξη που θα αποκαλυφθεί
    char line[MAX_WORD_LENGTH];       // Η γραμμή εισόδου
    int word_length = 0;              // Το μήκος της λέξης

    // Ανάγνωση γραμμών από την πρότυπη είσοδο
    while (fgets(line, sizeof(line), stdin)) {
        // Αφαίρεση του χαρακτήρα νέας γραμμής
        line[strcspn(line, "\n")] = '\0';

        // Αφαίρεση κενών διαστημάτων από την αρχή και το τέλος
        trim(line);

        // Αν είναι η πρώτη γραμμή, καθορισμός του μήκους της λέξης
        if (word_length == 0) {
            word_length = strlen(line);

            // Έλεγχος για υπέρβαση μέγιστου επιτρεπτού μήκους
            if (word_length >= MAX_WORD_LENGTH) {
                fprintf(stderr, "Error: Word length exceeds maximum allowed length.\n");
                return 1;
            }

            // Αρχικοποίηση της λέξης με κάτω παύλες
            for (int i = 0; i < word_length; i++) {
                word[i] = '_';
            }
            word[word_length] = '\0';
        }

        // Έλεγχος αν η γραμμή έχει το ίδιο μήκος με τη λέξη
        if (strlen(line) != word_length) {
            fprintf(stderr, "Error: Inconsistent line lengths.\n");
            return 1;
        }

        // Ενημέρωση της λέξης με τα αποκαλυπτόμενα γράμματα
        for (int i = 0; i < word_length; i++) {
            if (isalpha((unsigned char)line[i])) {
                word[i] = line[i];
            }
        }
    }

    // Εκτύπωση της τελικής λέξης
    printf("%s\n", word);

    return 0;
}


// Μεταγλώττιση:
// gcc letter.c -o letter
// Δοκιμές:
// ./letter < reveal.txt