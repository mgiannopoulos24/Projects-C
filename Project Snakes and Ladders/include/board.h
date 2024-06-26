#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    int snakes[101];
    int ladders[101];
} Board;

void initBoard(Board *board);
int getBoardPosition(Board *board, int position);
void renderBoard(Board *board, SDL_Renderer *renderer, TTF_Font *);

#endif
