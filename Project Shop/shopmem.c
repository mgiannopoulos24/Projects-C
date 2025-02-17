#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_K 100
#define MAX_MONEY 10000

int memo[MAX_N][MAX_MONEY];

int maxMoneyMemoization(int M, int N, int *C[], int Ki[]) {
    if (N == 0 || M == 0) return 0;

    if (memo[N][M] != -1) return memo[N][M];

    int maxSpent = 0;

    for (int i = 0; i < Ki[N-1]; i++) {
        if (C[N-1][i] <= M) {
            int spent = C[N-1][i] + maxMoneyMemoization(M - C[N-1][i], N-1, C, Ki);
            if (spent > maxSpent)
                maxSpent = spent;
        }
    }

    memo[N][M] = maxSpent;
    return maxSpent;
}

int main() {
    int M, N;
    
    printf("Give the amount of money available: ");
    scanf("%d", &M);
    
    printf("Provide the number of products: ");
    scanf("%d", &N);
    
    int K[N];
    int *C[N]; 

    for (int i = 0; i < N; i++) {
        printf("Give the number of options for the product %d: ", i+1);
        scanf("%d", &K[i]);
        C[i] = malloc(K[i] * sizeof(int)); 
        printf("Give the cost of options for the product %d: ", i+1);
        for (int j = 0; j < K[i]; j++) {
            scanf("%d", &C[i][j]);
        }
    }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            memo[i][j] = -1;

    int maxSpent = maxMoneyMemoization(M, N, C, K);

    printf("The maximum amount we can spend is: %d\n", maxSpent);

    return 0;
}
