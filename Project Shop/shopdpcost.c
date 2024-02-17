#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_K 100
#define MAX_MONEY 10000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxMoneyDP(int M, int N, int *C[], int Ki[]) {
    int dp[N + 1][M + 1];

    // Initialisation of the dp matrix with zero values
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            dp[i][j] = 0;

    // We fill the dp table recursively
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k < Ki[i-1]; k++) {
                if (C[i-1][k] <= j) {
                    dp[i][j] = max(dp[i][j], C[i-1][k] + dp[i-1][j - C[i-1][k]]);
                }
            }
        }
    }

    return dp[N][M];
}

int main() {
    int M, N;
    
    // We ask the user for the number of products and the amount of money available
    printf("Provide the number of products: ");
    scanf("%d", &N);
    printf("Give the amount of money available: ");
    scanf("%d", &M);
    
    // We initialise the tables for the options and option numbers
    int K[N];
    int *C[N];
    
    // We read the options for each product from the user
    for (int i = 0; i < N; i++) {
        printf("Give the number of options for the product %d: ", i + 1);
        scanf("%d", &K[i]);
        
        C[i] = malloc(K[i] * sizeof(int));
        
        printf("Give the cost of options for the product %d: ", i + 1);
        for (int j = 0; j < K[i]; j++) {
            scanf("%d", &C[i][j]);
        }
    }

    // We call the function to find the maximum amount we can spend
    int maxSpent = maxMoneyDP(M, N, C, K);

    printf("The maximum amount we can spend is: %d\n", maxSpent);

    // Print costs if COSTS is defined
    #ifdef COSTS
    printf("The costs of the models to be purchased are:\n");
    for (int i = 0; i < N; i++) {
        printf("Product %d costs: ", i + 1);
        for (int j = 0; j < K[i]; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    #endif

    return 0;
}
