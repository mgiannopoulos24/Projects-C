#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define UPPER_LIMIT 1000000000000000ULL

long long int atoll(const char *nptr);

int isFlawlessSquare(long long int num) {
    if (num <= 0) return 0; // Negative numbers and zero are not flawless squares

    long long int temp = num;
    int digits[10] = {0}; // Array to store the digits

    // Calculate the sum of the digits
    int sum_of_digits = 0;
    while (temp > 0) {
        int digit = temp % 10;
        sum_of_digits += digit;
        digits[digit]++;
        temp /= 10;
    }

    // Check if the sum of the digits squared is a perfect square
    long long int sum_of_digits_squared = sum_of_digits * sum_of_digits;
    long long int sqrt_sum_of_digits_squared = sqrt(sum_of_digits_squared);
    if (sqrt_sum_of_digits_squared * sqrt_sum_of_digits_squared != sum_of_digits_squared) {
        return 0; // Sum of digits squared is not a perfect square
    }

    // Check if each digit is used exactly once
    for (int i = 1; i < 10; i++) {
        if (digits[i] != 1) {
            return 0; // Digit not used or used more than once
        }
    }

    return 1; // Number is a flawless square
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./flawless low high\n");
        return 1; // Exit with code 1
    }

    long long int low = atoll(argv[1]);
    long long int high = atoll(argv[2]);

    if (low <= 0 || high <= 0 || high < low || high > UPPER_LIMIT) {
        printf("Invalid boundaries\n");
        return 1; // Exit with code 1
    }

    long long int sum = 0;

    for (long long int i = low; i <= high; i++) {
        if (isFlawlessSquare(i)) {
            sum += i;
        }
    }

    printf("Sum of flawless squares in range [%lld, %lld]: %lld\n", low, high, sum);

    return 0;
}
