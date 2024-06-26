#include "game.h"
#include "dice.h"
#include <stdio.h>

void initGame(Game *game, SDL_Renderer *renderer) {
    game->renderer = renderer;
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }
    game->font = TTF_OpenFont("src/osans.ttf", 24);
    if (game->font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }
    initBoard(&game->board);
    initPlayer(&game->players[0], "Player 1");
    initPlayer(&game->players[1], "Player 2");
    game->currentPlayer = 0;
}

void handleEvent(Game *game, SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_SPACE) {
            int roll = rollDice();
            printf("Player %d rolled a %d\n", game->currentPlayer + 1, roll);
            movePlayer(&game->players[game->currentPlayer], roll, &game->board);
            if (game->players[game->currentPlayer].position >= 100) {
                printf("Player %d wins!\n", game->currentPlayer + 1);
                SDL_Quit();
                exit(0);
            }
            game->currentPlayer = (game->currentPlayer + 1) % 2;
        }
    }
}

void updateGame(Game *game) {
    // Update game logic if necessary
}

void renderGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);
    renderBoard(&game->board, game->renderer, game->font);
    renderPlayer(&game->players[0], game->renderer);
    renderPlayer(&game->players[1], game->renderer);
    SDL_RenderPresent(game->renderer); 
}

void destroyGame(Game *game) {
    TTF_CloseFont(game->font);
    TTF_Quit();
}
