#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK 5
#define NUM_THREADS 4 

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

typedef struct {
    int startNum;
    int endNum;
} ThreadData;

int count_sem = 0;
int count_kprim = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *computePrimes(void *threadarg) {
    ThreadData *my_data;
    my_data = (ThreadData *) threadarg;
    int num, k, divisor, piliko;

    for(num = my_data->startNum; num <= my_data->endNum; num++) {
        k = 0;
        divisor = 2;
        piliko = num;

        while (divisor <= piliko && k <= MAXK) {
            if (piliko % divisor == 0) {
                k++;
                piliko = piliko / divisor;
            } else {
                if (piliko > 1 && divisor * divisor > piliko) {
                    divisor = piliko;
                } else {
                    if (divisor == 2) divisor++; else divisor += 2;
                }
            }
        }

        pthread_mutex_lock(&mutex1);
        if (k == 2) {
            count_sem++;
        }
        if (k >= 2 & k <= MAXK) {
            count_kprim++;
        }
        pthread_mutex_unlock(&mutex1);
    }

    pthread_exit(NULL);
}

void* threadFunction(void* arg) {
    // Example read operation
    pthread_rwlock_rdlock(&rwlock);
    // Perform read operations on shared data
    pthread_rwlock_unlock(&rwlock);

    // Example write operation
    pthread_rwlock_wrlock(&rwlock);
    // Perform write operations on shared data
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data_array[NUM_THREADS];
    int rc;
    long t;
    void *status;

    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    int range = (MAXNUM - MINNUM + 1) / NUM_THREADS;

    for(t = 0; t < NUM_THREADS; t++) {
        thread_data_array[t].startNum = MINNUM + t * range;
        thread_data_array[t].endNum = MINNUM + (t+1) * range - 1;
        if (t == NUM_THREADS - 1) thread_data_array[t].endNum = MAXNUM;

        rc = pthread_create(&threads[t], NULL, computePrimes, (void *)&thread_data_array[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Found %d K-almost prime numbers (2<=K<=%d)\n", count_kprim, MAXK);
    printf("Found %d semiprimes\n", count_sem);
    printf("Execution time: %.3f seconds\n", elapsed);
    pthread_rwlock_destroy(&rwlock);
    pthread_exit(NULL);
}
