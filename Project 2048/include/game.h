#ifndef GAME_H
#define GAME_H

void init_game(int board[4][4]);
void add_new_element(int board[4][4]);
int make_move(int board[4][4], char move, int *score);
int is_game_over(int board[4][4]);

#endif
