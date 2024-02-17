#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_K 100
#define MAX_MONEY 10000

int memo[MAX_N][MAX_MONEY];

int maxMoneyMemorization(int M, int N, int *C[], int Ki[]) {
    if (N == 0 || M == 0) return 0;

    if (memo[N][M] != -1) return memo[N][M];

    int maxSpent = 0;

    for (int i = 0; i < Ki[N-1]; i++) {
        if (C[N-1][i] <= M) {
            int spent = C[N-1][i] + maxMoneyMemorization(M - C[N-1][i], N-1, C, Ki);
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

    int maxSpent = maxMoneyMemorization(M, N, C, K);

    printf("The maximum amount we can spend is: %d\n", maxSpent);

#ifdef COSTS
    // Print the costs of the models
    printf("Costs of selected models:\n");
    int remainingMoney = M;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < K[i]; j++) {
            if (C[i][j] <= remainingMoney && memo[i+1][remainingMoney - C[i][j]] == memo[i][remainingMoney - C[i][j]]) {
                printf("Product %d: $%d\n", i+1, C[i][j]);
                remainingMoney -= C[i][j];
                break;
            }
        }
    }
#endif

    return 0;
}
