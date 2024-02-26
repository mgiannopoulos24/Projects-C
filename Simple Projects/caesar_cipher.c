#include <stdio.h>

char encrypt(char ch, int shift) {
    if ('a' <= ch && ch <= 'z') {
        // Encrypt small letters
        return 'a' + (ch - 'a' + shift) % 26;
    } else if ('A' <= ch && ch <= 'Z') {
        // Encrypt capital letters
        return 'A' + (ch - 'A' + shift) % 26;
    } else {
        // Print character as is if not latin
        return ch;
    }
}

int main() {
    const int shift = 13; // Shift for Caesar Cipher
    char ch;

    printf("Enter text to encrypt:\n");
    while ((ch = getchar()) != EOF && ch != '\n') {
        putchar(encrypt(ch, shift));
    }

    return 0;
}
