#include "board.h"

int combine_tiles(int *row_or_col, int *score) {
    int moved = 0;
    for (int i = 0; i < 3; i++) {
        if (row_or_col[i] != 0 && row_or_col[i] == row_or_col[i + 1]) {
            row_or_col[i] *= 2;
            row_or_col[i + 1] = 0;
            *score += row_or_col[i];
            moved = 1;
        }
    }
    return moved;
}

int shift_tiles(int *row_or_col) {
    int moved = 0;
    for (int i = 0; i < 3; i++) {
        if (row_or_col[i] == 0) {
            for (int j = i + 1; j < 4; j++) {
                if (row_or_col[j] != 0) {
                    row_or_col[i] = row_or_col[j];
                    row_or_col[j] = 0;
                    moved = 1;
                    break;
                }
            }
        }
    }
    return moved;
}

int move_up(int board[4][4], int *score) {
    int moved = 0;
    for (int col = 0; col < 4; col++) {
        int col_array[4];
        for (int row = 0; row < 4; row++) {
            col_array[row] = board[row][col];
        }
        moved |= shift_tiles(col_array);
        moved |= combine_tiles(col_array, score);
        moved |= shift_tiles(col_array);
        for (int row = 0; row < 4; row++) {
            board[row][col] = col_array[row];
        }
    }
    return moved;
}

int move_down(int board[4][4], int *score) {
    int moved = 0;
    for (int col = 0; col < 4; col++) {
        int col_array[4];
        for (int row = 0; row < 4; row++) {
            col_array[row] = board[3-row][col];
        }
        moved |= shift_tiles(col_array);
        moved |= combine_tiles(col_array, score);
        moved |= shift_tiles(col_array);
        for (int row = 0; row < 4; row++) {
            board[3-row][col] = col_array[row];
        }
    }
    return moved;
}

int move_left(int board[4][4], int *score) {
    int moved = 0;
    for (int row = 0; row < 4; row++) {
        moved |= shift_tiles(board[row]);
        moved |= combine_tiles(board[row], score);
        moved |= shift_tiles(board[row]);
    }
    return moved;
}

int move_right(int board[4][4], int *score) {
    int moved = 0;
    for (int row = 0; row < 4; row++) {
        int row_array[4];
        for (int col = 0; col < 4; col++) {
            row_array[col] = board[row][3-col];
        }
        moved |= shift_tiles(row_array);
        moved |= combine_tiles(row_array, score);
        moved |= shift_tiles(row_array);
        for (int col = 0; col < 4; col++) {
            board[row][3-col] = row_array[col];
        }
    }
    return moved;
}
