#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "board.h"

void init_game(int board[4][4]) {
    add_new_element(board);
    add_new_element(board);
}

void add_new_element(int board[4][4]) {
    int empty_tiles[16][2];
    int empty_count = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                empty_tiles[empty_count][0] = i;
                empty_tiles[empty_count][1] = j;
                empty_count++;
            }
        }
    }
    
    if (empty_count > 0) {
        int chosen_tile = rand() % empty_count;
        int i = empty_tiles[chosen_tile][0];
        int j = empty_tiles[chosen_tile][1];
        board[i][j] = (rand() % 2 + 1) * 2;
    }
}

int make_move(int board[4][4], char move, int *score) {
    int moved = 0;
    switch (move) {
        case 'w':
            moved = move_up(board, score);
            break;
        case 's':
            moved = move_down(board, score);
            break;
        case 'a':
            moved = move_left(board, score);
            break;
        case 'd':
            moved = move_right(board, score);
            break;
        default:
            printf("Invalid move!\n");
            break;
    }
    return moved;
}

int is_game_over(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return 0;
            if (i < 3 && board[i][j] == board[i+1][j]) return 0;
            if (j < 3 && board[i][j] == board[i][j+1]) return 0;
        }
    }
    return 1;
}
