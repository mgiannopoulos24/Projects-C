#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

int solveSudoku(int grid[N][N]);
void printGrid(int grid[N][N]);
int isSafe(int grid[N][N], int row, int col, int num);
int findEmptyLocation(int grid[N][N], int *row, int *col);
void readGrid(int grid[N][N], const char *filename);

#endif
