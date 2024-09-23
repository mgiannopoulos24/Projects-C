#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BLINK "\x1b[5m"
#define RESET "\x1b[0m"

int main() {
    char ch;
    char word[100];
    int idx = 0;
    int in_word = 0;

    // Διαβάζουμε χαρακτήρα-χαρακτήρα από το stdin
    while ((ch = getchar()) != EOF) {
        if (isalpha(ch)) {
            // Βρισκόμαστε μέσα σε μια λέξη
            word[idx++] = ch;
            in_word = 1;
        } else {
            if (in_word) {
                // Τέλος λέξης, ελέγχουμε αν είναι η λέξη "Blinky"
                word[idx] = '\0';
                if (strcmp(word, "Blinky") == 0) {
                    // Τυπώνουμε τη λέξη με αστεράκια και εφέ αναβοσβήνει
                    printf("*" BLINK "%s" RESET "*", word);
                } else {
                    // Τυπώνουμε τη λέξη όπως είναι
                    printf("%s", word);
                }
                idx = 0;
                in_word = 0;
            }
            // Τυπώνουμε τον χαρακτήρα διαχωριστικό
            putchar(ch);
        }
    }

    // Έλεγχος αν το αρχείο τελείωσε εν μέσω λέξης
    if (in_word) {
        word[idx] = '\0';
        if (strcmp(word, "Blinky") == 0) {
            printf("*" BLINK "%s" RESET "*", word);
        } else {
            printf("%s", word);
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc blinky.c -o blinky
// Εκτέλεση:
// ./blinky < description.txt