#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int is_square_of_prime(int num) {
    int root = (int)sqrt(num);
    return (root * root == num) && is_prime(root);
}

int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int is_palindromic(int num) {
    return num == reverse_number(num);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s low high\n", argv[0]);
        return 1;
    }

    int64_t low = atoi(argv[1]);
    int64_t high = atoi(argv[2]);

    if (low <= 0 || high <= 0 || low > high) {
        fprintf(stderr, "Error: Arguments must be positive integers and 'low' should be less than or equal to 'high'.\n");
        return 1;
    }

    int64_t sum = 0; // To hold the sum of the numbers meeting the criteria

    for (int64_t base = (int64_t)sqrt(low); base * base <= high; base++) {
        if (is_prime(base)) {
            int64_t square = base * base;
            if (!is_palindromic(square)) {
                int64_t mirror = reverse_number(square);
                // Check if the mirror is within the range and is a square of a prime
                if (mirror <= high && is_square_of_prime(mirror) && !is_palindromic(mirror)) {
                    printf("%lld and its mirror %lld are both squares of a prime and not palindromic.\n", square, mirror);
                    sum += square;
                }
            }
        }
    }
    printf("The sum of all numbers meeting the criteria is: %lld\n", sum);

    return 0;
}
