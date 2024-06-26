#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "player.h"
#include "board.h"

typedef struct {
    Player players[2];
    int currentPlayer;
    Board board;
    SDL_Renderer *renderer;
    TTF_Font *font;
} Game;

void initGame(Game *game, SDL_Renderer *renderer);
void handleEvent(Game *game, SDL_Event *e);
void updateGame(Game *game);
void renderGame(Game *game);
void destroyGame(Game *game);

#endif
