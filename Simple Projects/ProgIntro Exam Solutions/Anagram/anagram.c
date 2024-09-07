#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Συνάρτηση για να αφαιρέσει μη αλφαριθμητικούς χαρακτήρες και να μετατρέψει σε πεζά
void preprocess(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (isalpha((unsigned char)*src)) {
            *dst++ = tolower((unsigned char)*src);
        }
        src++;
    }
    *dst = '\0';
}

// Συνάρτηση για να μετρήσει τους χαρακτήρες μιας συμβολοσειράς
void count_chars(const char *str, int *count) {
    while (*str) {
        count[(unsigned char)*str]++;
        str++;
    }
}

// Συνάρτηση για να ελέγξει αν δύο φράσεις είναι αναγράμματα
int are_anagrams(const char *str1, const char *str2) {
    int count1[256] = {0};
    int count2[256] = {0};

    // Αφαιρούμε μη αλφαριθμητικούς χαρακτήρες και μετατρέπουμε σε πεζά
    char processed1[1000];
    char processed2[1000];
    strncpy(processed1, str1, sizeof(processed1) - 1);
    strncpy(processed2, str2, sizeof(processed2) - 1);
    preprocess(processed1);
    preprocess(processed2);

    // Μετράμε τους χαρακτήρες
    count_chars(processed1, count1);
    count_chars(processed2, count2);

    // Συγκρίνουμε τις μετρήσεις χαρακτήρων
    for (int i = 0; i < 256; i++) {
        if (count1[i] != count2[i]) {
            return 0; // Όχι αναγράμματα
        }
    }
    return 1; // Αναγράμματα
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"phrase1\" \"phrase2\"\n", argv[0]);
        return 1;
    }

    if (are_anagrams(argv[1], argv[2])) {
        printf("\"%s\" is an anagram of \"%s\".\n", argv[1], argv[2]);
    } else {
        printf("\"%s\" is NOT an anagram of \"%s\".\n", argv[1], argv[2]);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc anagram.c -o anagram
// Δοκιμές:
// ./anagram "desert you!" "you rested!"
// ./anagram "never gonna give" "never gonna give"
// ./anagram "never gonna give" "gonna run around"