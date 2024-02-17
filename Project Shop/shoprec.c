#include <stdio.h>
#include <stdlib.h>
// Function for the recursive solution of the problem
int maxMoneyRecursive(int M, int N, int *C[], int Ki[]) {
    // Basis of recourse: if there are no products or no money available
    if (N == 0 || M == 0) return 0;

    int maxSpent = 0;

    // For each product option
    for (int i = 0; i < Ki[N-1]; i++) {
        // If the cost of the option is less than the money available
        if (C[N-1][i] <= M) {
            // Calculate the maximum amount we can spend on the remaining products
            int spent = C[N-1][i] + maxMoneyRecursive(M - C[N-1][i], N-1, C, Ki);
            // We update the maximum amount we can spend
            if (spent > maxSpent)
                maxSpent = spent;
        }
    }

    return maxSpent;
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
    int maxSpent = maxMoneyRecursive(M, N, C, K);

    printf("The maximum amount we can spend is: %d\n", maxSpent);

    return 0;
}
