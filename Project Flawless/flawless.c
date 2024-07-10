#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to check if a number is a perfect square
int is_perfect_square(long long num) {
    long long sqrt_num = (long long)sqrt(num);
    return (sqrt_num * sqrt_num == num);
}

// Function to calculate the sum of a list of digits
long long sum_of_digits(const char *digits, int start, int end) {
    long long sum = 0;
    for (int i = start; i <= end; ++i) {
        sum = sum * 10 + (digits[i] - '0');
    }
    return sum;
}

// Recursive function to check all digit groupings
int check_groupings(const char *digits, int len, int start, long long current_sum, long long original_num) {
    if (start == len) {
        return (current_sum * current_sum == original_num);
    }

    long long num = 0;
    for (int i = start; i < len; ++i) {
        num = num * 10 + (digits[i] - '0');
        if (check_groupings(digits, len, i + 1, current_sum + num, original_num)) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a number is a flawless square
int is_flawless_square(long long num) {
    if (!is_perfect_square(num)) {
        return 0;
    }

    char digits[20];
    sprintf(digits, "%lld", num);
    int len = strlen(digits);

    return check_groupings(digits, len, 0, 0, num);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return 1;
    }

    long long start = atoll(argv[1]);
    long long end = atoll(argv[2]);
    long long sum_flawless_squares = 0;

    for (long long i = start; i <= end; i++) {
        if (is_flawless_square(i)) {
            sum_flawless_squares += i;
        }
    }

    printf("%lld\n", sum_flawless_squares);
    return 0;
}
