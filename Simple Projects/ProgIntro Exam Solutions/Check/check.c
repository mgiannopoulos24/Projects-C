#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

int main(int argc, char *argv[]) {
    // Έλεγχος αν έχουν δοθεί τουλάχιστον δύο ορίσματα
    if (argc < 3) {
        fprintf(stderr, "Error: Insufficient arguments. Usage: %s <target_word> <guess1> [<guess2> ...]\n", argv[0]);
        return 1;
    }

    // Ανάκτηση της λέξης στόχου
    char *target = argv[1];
    int word_length = strlen(target);

    // Μετατροπή της λέξης στόχου σε πεζά
    for (int i = 0; i < word_length; i++) {
        target[i] = tolower((unsigned char)target[i]);
    }

    // Επεξεργασία κάθε προσπάθειας
    for (int g = 2; g < argc; g++) {
        char guess[MAX_WORD_LENGTH];
        strncpy(guess, argv[g], MAX_WORD_LENGTH - 1);
        guess[MAX_WORD_LENGTH - 1] = '\0';

        // Έλεγχος αν η προσπάθεια έχει το σωστό μήκος
        if (strlen(guess) != word_length) {
            fprintf(stderr, "Error: Guess '%s' does not match the target word length.\n", guess);
            continue;
        }

        // Μετατροπή της προσπάθειας σε πεζά
        for (int i = 0; i < word_length; i++) {
            guess[i] = tolower((unsigned char)guess[i]);
        }

        int correct_position = 0;
        int correct_letter_wrong_position = 0;

        int target_letter_count[256] = {0};
        int guess_letter_count[256] = {0};

        // Πρώτη διέλευση: Βρίσκουμε τα γράμματα στη σωστή θέση
        for (int i = 0; i < word_length; i++) {
            if (guess[i] == target[i]) {
                correct_position++;
            } else {
                // Μετράμε τα γράμματα που δεν είναι στη σωστή θέση
                target_letter_count[(unsigned char)target[i]]++;
                guess_letter_count[(unsigned char)guess[i]]++;
            }
        }

        // Δεύτερη διέλευση: Βρίσκουμε τα σωστά γράμματα σε λάθος θέση
        for (int i = 0; i < 256; i++) {
            int min_count = target_letter_count[i] < guess_letter_count[i] ? target_letter_count[i] : guess_letter_count[i];
            correct_letter_wrong_position += min_count;
        }

        // Εκτύπωση του αποτελέσματος για την τρέχουσα προσπάθεια
        printf("%s has %d correct letters in correct position and %d correct letters in an incorrect position\n",
               argv[g], correct_position, correct_letter_wrong_position);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc check.c -o check
// Δοκιμές:
// ./check unlit legal vinyl sling inlet unlit
// ./check hello world worll wrllo