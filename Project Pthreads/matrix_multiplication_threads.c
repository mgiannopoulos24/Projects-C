#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

int A[N][N], B[N][N], C[N][N];

void *multiply_row(void *arg) {
    int row = *(int *)arg;
    for (int i = 0; i < N; i++) {
        C[row][i] = 0;
        for (int j = 0; j < N; j++) {
            C[row][i] += A[row][j] * B[j][i];
        }
    }
    pthread_exit(0);
}

int main() {
    pthread_t threads[N];
    int thread_ids[N];

    // Initialize matrices
    printf("Matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 10;
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Create threads to compute rows of matrix C
    for (int i = 0; i < N; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply_row, (void *)&thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display result
    printf("Resultant Matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
