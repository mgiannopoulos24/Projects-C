#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

void process_word(char *word) {
    printf("pika%s ", word);
}

int main() {
    char c;
    char word[MAX_WORD_LENGTH];
    int word_index = 0;

    // Διαβάζουμε χαρακτήρα προς χαρακτήρα
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) { // Εάν είναι γράμμα, το αποθηκεύουμε στη λέξη
            if (word_index < MAX_WORD_LENGTH - 1) {
                word[word_index++] = c;
            }
        } else {
            if (word_index > 0) { // Αν βρούμε μη γράμμα, τυπώνουμε τη λέξη
                word[word_index] = '\0';
                process_word(word);
                word_index = 0;
            }
            if (!isspace(c)) { // Εκτυπώνουμε το μη γράμμα (π.χ. , ! ?)
                putchar(c);
            }
        }
    }

    // Αν η λέξη τελειώνει με EOF
    if (word_index > 0) {
        word[word_index] = '\0';
        process_word(word);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc pika.c -o pika
// Εκτέλεση:
// ./pika < ash.txt