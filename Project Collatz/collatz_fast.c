#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> // Include the OpenMP header

#define LIMIT 1000000

unsigned long collatz_cache[LIMIT] = {0};

unsigned long collatz_sequence_length(unsigned long long n) {
    unsigned long length = 1;
    unsigned long long original_n = n;
    while (n != 1) {
        if (n < LIMIT && collatz_cache[n] != 0) {
            length += collatz_cache[n] - 1;
            break;
        }
        if (n & 1) {
            n = n * 3 + 1;
            if (n < LIMIT && collatz_cache[n] != 0) {
                // Check cache again in case the new n is in the cache
                length += collatz_cache[n];
                break;
            }
            n >>= 1; // Apply bitwise operation for division by 2
            length += 2;
        } else {
            n >>= 1;
            length++;
        }
    }
    if (original_n < LIMIT) {
        collatz_cache[original_n] = length;
    }
    return length;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start number> <end number>\n", argv[0]);
        return 1;
    }

    // Set the number of threads to 4
    omp_set_num_threads(4);

    unsigned long long start = strtoull(argv[1], NULL, 10);
    unsigned long long end = strtoull(argv[2], NULL, 10);
    unsigned long max_sequence_length = 0;
    unsigned long long number_with_max_length = 0;

    clock_t begin = clock();

    #pragma omp parallel for reduction(max:max_sequence_length) proc_bind(spread)
    for (unsigned long long i = start; i <= end; ++i) {
        unsigned long current_length = collatz_sequence_length(i);
        if (current_length > max_sequence_length) {
            #pragma omp critical
            {
                if (current_length > max_sequence_length) { // Check again to avoid race condition
                    max_sequence_length = current_length;
                    number_with_max_length = i;
                }
            }
        }
    }

    clock_t end_time = clock();
    double time_spent = (double)(end_time - begin) / CLOCKS_PER_SEC;

    printf("Number with the longest Collatz sequence in range %llu to %llu: %llu\n", start, end, number_with_max_length);
    printf("Length of the longest Collatz sequence: %lu\n", max_sequence_length);
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
