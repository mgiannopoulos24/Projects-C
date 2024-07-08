#include <stdio.h>

int main() {
    int num, sum, digit;

    // Prompt the user to enter an integer
    printf("Enter an integer: ");
    scanf("%d", &num);

    // Repeat the process until the number becomes a single-digit number
    while (num > 9) {
        sum = 0;

        // Calculate the sum of the digits of the number
        while (num > 0) {
            digit = num % 10;  // Extract the last digit
            sum += digit;      // Add the digit to the sum
            num /= 10;         // Remove the last digit
        }

        // Display the sum of the digits
        printf("Sum of digits: %d\n", sum);

        // Update the number with the calculated sum for the next iteration
        num = sum;
    }

    // Display the resulting single-digit number
    printf("The single-digit number is: %d\n", num);

    return 0;
}
