#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <sled_capacity> <weight1> <weight2> ...\n", argv[0]);
        return 1;
    }

    int sled_capacity = atoi(argv[1]);
    int num_weights = argc - 2;
    int *weights = malloc(num_weights * sizeof(int));
    if (weights == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Ανάγνωση των βαρών
    for (int i = 0; i < num_weights; i++) {
        weights[i] = atoi(argv[i + 2]);
    }

    int found = 0;

    // Έλεγχος όλων των συνδυασμών τριών βαρών
    for (int i = 0; i < num_weights - 2; i++) {
        for (int j = i + 1; j < num_weights - 1; j++) {
            for (int k = j + 1; k < num_weights; k++) {
                if (weights[i] + weights[j] + weights[k] == sled_capacity) {
                    printf("You can take 3 objects: %d + %d + %d = %d\n",
                           weights[i], weights[j], weights[k], sled_capacity);
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("No 3 objects found to fill up your sled.\n");
    }

    free(weights);
    return 0;
}

// Μεταγλώττιση:
// gcc sled.c -o sled
// Εκτέλεση:
// ./sled 42 18 1 4 81 47 35 22 41 2 3 17
// ./sled 42 18 1 4 81 47 35 41 2 17
