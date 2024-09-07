#include <stdio.h>
#include <ctype.h>

// Συνάρτηση για την εφαρμογή του αλγορίθμου κρυπτογράφησης του Καίσαρα
char caesar_cipher(char c, int shift) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        return (c - base + shift) % 26 + base;
    }
    return c;
}

int main() {
    char c;
    const int shift = 13;

    // Διαβάζει χαρακτήρες από την είσοδο και κρυπτογραφεί το κείμενο
    while ((c = getchar()) != EOF) {
        putchar(caesar_cipher(c, shift));
    }

    return 0;
}

// Μεταγλώττιση:
// gcc caesar.c -o caesar
// Δοκιμές:
// ./caesar < toto.txt