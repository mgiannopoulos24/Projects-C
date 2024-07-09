#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_LIST_FILE "words.txt"

bool choose_random_word(char *word) {
    FILE *file = fopen(WORD_LIST_FILE, "r");
    if (!file) {
        return false;
    }

    char buffer[MAX_WORD_LENGTH];

    while (fgets(buffer, MAX_WORD_LENGTH, file)) {
        // Remove newline character and any trailing whitespace
        size_t length = strlen(buffer);
        if (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
            buffer[length - 1] = '\0';  // Remove newline
        }
        if (length > 1 && (buffer[length - 2] == '\n' || buffer[length - 2] == '\r')) {
            buffer[length - 2] = '\0';  // Remove additional carriage return if present
        }

        // Copy the word to the output parameter
        strcpy(word, buffer);
        fclose(file);
        return true;
    }

    fclose(file);
    return false;  // No words found in the file
}
