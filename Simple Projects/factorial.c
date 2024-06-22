#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int number;
    unsigned long long fact = 1;

    // Prompt user to enter a number
    printf("Enter a non-negative integer to calculate its factorial: ");
    scanf("%d", &number);

    // Check if the number is negative
    if (number < 0) {
        printf("Error: Factorial of a negative number doesn't exist.\n");
    } else {
        // Calculate factorial using recursive function
        fact = factorial(number);
        printf("Factorial of %d = %llu\n", number, fact);
    }

    return 0;
}
