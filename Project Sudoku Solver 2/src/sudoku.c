#include <stdio.h>
#include "sudoku.h"

// Function to find an empty location in the grid
int findEmptyLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Function to check if it's safe to place a number in a given cell
int isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return 0;
        }
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Recursive function to solve the Sudoku puzzle using backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;

    if (!findEmptyLocation(grid, &row, &col)) {
        return 1;
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return 1;
            }

            grid[row][col] = 0;
        }
    }

    return 0;
}

// Function to print the Sudoku grid with separators
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("------+-------+------\n");
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                printf("| ");
            }
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}
