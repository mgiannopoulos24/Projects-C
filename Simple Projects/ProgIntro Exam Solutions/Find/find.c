#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 1000

void print_word_with_highlight(const char *word, const char *subseq) {
    const char *pos = word;
    const char *start = word;
    size_t subseq_len = strlen(subseq);

    while ((pos = strstr(pos, subseq)) != NULL) {
        // Εκτύπωση μέρους πριν την υπακολουθία
        fwrite(start, 1, pos - start, stdout);
        // Εκτύπωση της υπακολουθίας με έντονα γράμματα
        printf("\033[1m");
        fwrite(pos, 1, subseq_len, stdout);
        printf("\033[0m");
        // Μετακίνηση του δείκτη μετά την υπακολουθία
        pos += subseq_len;
        start = pos;
    }

    // Εκτύπωση του υπολοίπου της λέξης
    if (*start) {
        printf("%s", start);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <substring>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *subseq = argv[2];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) == 1) {
        if (strstr(word, subseq) != NULL) {
            print_word_with_highlight(word, subseq);
            printf("\n");
        }
    }

    fclose(file);
    return 0;
}

// Μεταγλώττιση:
// gcc find.c -o find
// Εκτέλεση:
// ./find test.txt e