#include <stdio.h>
#include "sudoku.h"

int main() {
    int grid[N][N];
    readGrid(grid, "sudoku.txt");

    printf("Original Sudoku:\n");
    printGrid(grid);

    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
