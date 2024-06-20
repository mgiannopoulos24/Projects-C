#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "palindrome.h"

int main() {
    char input[100];
    int num;
    bool is_integer = true;

    printf("Enter a string or an integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Remove the newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Check if the input is an integer
    if (sscanf(input, "%d", &num) != 1) {
        is_integer = false;
    }

    // Determine which type of input it is and check palindrome
    if (is_integer) {
        if (is_int_palindrome(num)) {
            printf("%d is a palindrome.\n", num);
        } else {
            printf("%d is not a palindrome.\n", num);
        }
    } else {
        if (is_string_palindrome(input)) {
            printf("\"%s\" is a palindrome.\n", input);
        } else {
            printf("\"%s\" is not a palindrome.\n", input);
        }
    }

    return 0;
}
