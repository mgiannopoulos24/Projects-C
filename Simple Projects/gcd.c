#include <stdio.h>

// Function to calculate gcd
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;

    // Read 2 integers from command line
    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    // Print gcd
    printf("The Greatest Common Divisor of %d and %d is %d.\n", num1, num2, gcd(num1, num2));

    return 0;
}
