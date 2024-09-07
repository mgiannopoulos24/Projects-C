#include <stdio.h>
#include <ctype.h>

// Συνάρτηση για να προσθέσουμε νιφάδες σε μια λέξη
void add_snowflakes(const char *word) {
    // Βαθμός της λέξης
    int len = 0;
    while (word[len] && isalpha(word[len])) {
        len++;
    }

    if (len <= 1) {
        // Αν η λέξη έχει 1 ή λιγότερους χαρακτήρες, εκτυπώνουμε όπως είναι
        printf("%s", word);
    } else {
        // Αν η λέξη έχει περισσότερους χαρακτήρες, προσθέτουμε νιφάδες
        for (int i = 0; i < len - 1; i++) {
            printf("%c*", word[i]);
        }
        printf("%c", word[len - 1]); // Εκτύπωση του τελευταίου χαρακτήρα χωρίς νιφάδα
    }
}

int main() {
    int c;
    char word[1000];
    int index = 0;

    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            // Δημιουργία λέξης
            word[index++] = c;
        } else {
            if (index > 0) {
                word[index] = '\0'; // Τερματισμός της λέξης
                add_snowflakes(word);
                index = 0;
            }
            // Εκτύπωση του μη αλφαβητικού χαρακτήρα (π.χ., κενό, κόμμα)
            putchar(c);
        }
    }

    // Εκτύπωση της τελευταίας λέξης αν υπάρχει
    if (index > 0) {
        word[index] = '\0';
        add_snowflakes(word);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc snow.c -o snow
// Εκτέλεση:
// ./snow < elsa.txt