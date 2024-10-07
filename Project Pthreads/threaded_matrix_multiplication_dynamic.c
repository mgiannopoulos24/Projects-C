#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct {
    int row;
    int (*A)[N];
    int (*B)[N];
    int (*C)[N];
} ThreadArgs;

void *multiply_row(void *args) {
    ThreadArgs *data = (ThreadArgs *)args;
    int row = data->row;

    for (int i = 0; i < N; i++) {
        data->C[row][i] = 0;
        for (int j = 0; j < N; j++) {
            data->C[row][i] += data->A[row][j] * data->B[j][i];
        }
    }

    return NULL;
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    pthread_t threads[N];
    ThreadArgs thread_data[N];

    // Initialize matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Create threads to multiply rows
    for (int i = 0; i < N; i++) {
        thread_data[i].row = i;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        pthread_create(&threads[i], NULL, multiply_row, &thread_data[i]);
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
