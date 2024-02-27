#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to compute the length of the Collatz sequence for a given number
unsigned long collatz_sequence_length(unsigned long long n) {
    unsigned long length = 1; // Start with length 1 to include the starting number
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        length++;
    }
    return length;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start number> <end number>\n", argv[0]);
        return 1;
    }

    unsigned long long start = strtoull(argv[1], NULL, 10);
    unsigned long long end = strtoull(argv[2], NULL, 10);
    unsigned long max_sequence_length = 0;
    unsigned long long number_with_max_length = 0;
    unsigned long current_length;

    // Start the timer
    clock_t begin = clock();

    // Find the number with the longest Collatz sequence in the given range
    for (unsigned long long i = start; i <= end; ++i) {
        current_length = collatz_sequence_length(i);
        if (current_length > max_sequence_length) {
            max_sequence_length = current_length;
            number_with_max_length = i;
        }
    }

    // Stop the timer
    clock_t end_time = clock();

    // Calculate the time spent
    double time_spent = (double)(end_time - begin) / CLOCKS_PER_SEC;

    // Print the result
    printf("Number with the longest Collatz sequence in range %llu to %llu: %llu\n", start, end, number_with_max_length);
    printf("Length of the longest Collatz sequence: %lu\n", max_sequence_length);
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
