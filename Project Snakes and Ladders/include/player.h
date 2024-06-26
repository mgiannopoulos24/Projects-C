#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

typedef struct {
    char name[50];
    int position;
} Player;

void initPlayer(Player *player, const char *name);
void movePlayer(Player *player, int roll, Board *board);
void renderPlayer(Player *player, SDL_Renderer *renderer);

#endif
