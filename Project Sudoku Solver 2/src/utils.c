#include <stdio.h>
#include "sudoku.h"

// Function to read the Sudoku grid from a file
void readGrid(int grid[N][N], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            fscanf(file, "%d", &grid[row][col]);
        }
    }

    fclose(file);
}
