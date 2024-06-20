#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "palindrome.h"

// Function to check if a given string is a palindrome
bool is_string_palindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        while (left < right && !isalnum(str[right])) {
            right--;
        }

        // Compare characters, ignoring case
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

// Function to check if a given integer is a palindrome
bool is_int_palindrome(int num) {
    char str[20]; // Assuming a reasonable length for integer to string conversion

    // Convert integer to string
    sprintf(str, "%d", num);

    // Use string palindrome checker
    return is_string_palindrome(str);
}
