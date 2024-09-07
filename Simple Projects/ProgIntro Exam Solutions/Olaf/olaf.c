#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Συνάρτηση για την υπολογισμό του κόστους για μια συγκεκριμένη θέση
int calculate_cost(int x, int y, int **piles, int num_piles) {
    int cost = 0;
    for (int i = 0; i < num_piles; i++) {
        int dx = abs(piles[i][0] - x);
        int dy = abs(piles[i][1] - y);
        cost += dx + dy;
    }
    return cost;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    int **piles = NULL;
    int num_piles = 0;
    while (!feof(file)) {
        int x, y;
        if (fscanf(file, "%d %d", &x, &y) == 2) {
            piles = realloc(piles, (num_piles + 1) * sizeof(int *));
            piles[num_piles] = malloc(2 * sizeof(int));
            piles[num_piles][0] = x;
            piles[num_piles][1] = y;
            num_piles++;
        }
    }
    fclose(file);

    int min_cost = INT_MAX;
    int best_x = 0, best_y = 0;

    // Βρείτε τη θέση με το ελάχιστο κόστος
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cost = calculate_cost(i, j, piles, num_piles);
            if (cost < min_cost) {
                min_cost = cost;
                best_x = i;
                best_y = j;
            }
        }
    }

    // Εκτύπωση του αποτελέσματος
    printf("We will position the snowman on (%d, %d) with a minimum cost of %d.\n",
           best_x, best_y, min_cost);

    // Απελευθέρωση της μνήμης
    for (int i = 0; i < num_piles; i++) {
        free(piles[i]);
    }
    free(piles);

    return 0;
}

// Μεταγλώττιση:
// gcc olaf.c -o olaf
// Εκτέλεση:
// ./olaf map.txt