#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Συνάρτηση για να αντικαταστήσει τις λέξεις "up" και "down"
void replace_words(const char *input, char *output) {
    const char *src = input;
    char *dst = output;
    char word[MAX_WORD_LENGTH];
    int index;

    while (*src) {
        // Αναγνωρίζουμε λέξεις
        while (*src && isspace((unsigned char)*src)) {
            *dst++ = *src++;
        }

        index = 0;
        while (*src && !isspace((unsigned char)*src)) {
            word[index++] = *src++;
        }
        word[index] = '\0';

        // Ελέγχουμε αν η λέξη είναι "up" ή "down" και κάνουμε την αντικατάσταση
        if (strcmp(word, "up") == 0) {
            strcpy(dst, "down");
            dst += 4; // Length of "down"
        } else if (strcmp(word, "down") == 0) {
            strcpy(dst, "up");
            dst += 2; // Length of "up"
        } else {
            strcpy(dst, word);
            dst += strlen(word);
        }
        
        // Αντιγράφουμε το διαχωριστικό κενό ή χαρακτήρα νέας γραμμής
        if (*src == ' ' || *src == '\n') {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
}

int main() {
    char input[10000];   // Buffer για την είσοδο
    char output[10000];  // Buffer για την έξοδο

    // Διαβάζουμε το κείμενο από την πρότυπη είσοδο
    if (fread(input, 1, sizeof(input) - 1, stdin) <= 0) {
        perror("Error reading input");
        return 1;
    }

    // Τελειώνουμε τη συμβολοσειρά εισόδου
    input[sizeof(input) - 1] = '\0';

    // Κάνουμε την αντικατάσταση των λέξεων
    replace_words(input, output);

    // Εκτυπώνουμε το τροποποιημένο κείμενο στην πρότυπη έξοδο
    printf("%s", output);

    return 0;
}


// Μεταγλώττιση:
// gcc updown.c -o updown
// Δοκιμές:
// ./updown < rick.txt