#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



#define LIMIT 100000001
#define NUM_THREADS 4

unsigned long collatz_cache[LIMIT] = {0};
unsigned long max_sequence_length = 0;
unsigned long long number_with_max_length = 0;
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


typedef struct {
    unsigned long long start;
    unsigned long long end;
} ThreadData;

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

void* thread_worker(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    unsigned long local_max_length = 0;
    unsigned long long local_number_with_max_length = 0;
    
    for (unsigned long long i = data->start; i <= data->end; ++i) {
        unsigned long current_length = collatz_sequence_length(i);
        if (current_length > local_max_length) {
            local_max_length = current_length;
            local_number_with_max_length = i;
        }
    }
    
    // Update global maximum under write lock
    pthread_rwlock_wrlock(&lock);
    if (local_max_length > max_sequence_length) {
        max_sequence_length = local_max_length;
        number_with_max_length = local_number_with_max_length;
    }
    pthread_rwlock_unlock(&lock);
    
    pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start number> <end number>\n", argv[0]);
        return 1;
    }

    unsigned long long start = strtoull(argv[1], NULL, 10);
    unsigned long long end = strtoull(argv[2], NULL, 10);
    unsigned long long range_per_thread = (end - start + 1) / NUM_THREADS;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    clock_t begin = clock();

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = start + i * range_per_thread;
        thread_data[i].end = (i == NUM_THREADS - 1) ? end : thread_data[i].start + range_per_thread - 1;
        pthread_create(&threads[i], NULL, thread_worker, &thread_data[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    clock_t end_time = clock();
    double time_spent = (double)(end_time - begin) / CLOCKS_PER_SEC;

    printf("Length of the longest Collatz sequence: %lu\n", max_sequence_length);
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
