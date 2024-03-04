#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define UPPER_LIMIT 1000000000000000ULL

unsigned long long mirror(unsigned long long n) {
    unsigned long long rev = 0;
    while (n != 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int isperfectsq(unsigned long long x) {
    unsigned long long root = sqrt(x);
    return (root * root == x);
}

void sieve_of_eratosthenes(char *is_prime, unsigned long long limit) {
    for (unsigned long long i = 2; i <= limit; i++) {
        is_prime[i] = 1;
    }

    for (unsigned long long num = 2; num * num <= limit; num++) {
        if (is_prime[num]) {
            for (unsigned long long multiple = num * num; multiple <= limit; multiple += num) {
                is_prime[multiple] = 0;
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s low high\n", argv[0]);
        return 1;
    }

    unsigned long long low = strtoull(argv[1], NULL, 10);
    unsigned long long high = strtoull(argv[2], NULL, 10);

    if ((low > high) || (low < 1) || (high < 1) || (high > UPPER_LIMIT)) {
        printf("Input error!\n");
        return 1;
    }

    unsigned long long limit = sqrt(UPPER_LIMIT);
    char *is_prime = calloc(limit + 1, sizeof(char));
    sieve_of_eratosthenes(is_prime, limit);

    unsigned long long sum = 0;
    for (unsigned long long i = 1; i * i <= high; i++) {
        if (!is_prime[i]) continue; // Skip if i is not prime
        unsigned long long k = i * i;
        if (k < low) continue;
        unsigned long long mir = mirror(k);
        if (mir != k && mir <= high && isperfectsq(mir) && is_prime[(unsigned long long)sqrt(mir)]) {
            sum += k;
        }
    }

    printf("The sum is: %llu\n", sum);
    free(is_prime);
    return 0;
}
