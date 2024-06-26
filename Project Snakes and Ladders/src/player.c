#include "player.h"
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

void initPlayer(Player *player, const char *name) {
    strncpy(player->name, name, 50);
    player->position = 0;
}

void movePlayer(Player *player, int roll, Board *board) {
    player->position += roll;
    if (player->position > 100) {
        player->position = 100;
    }
    int newPosition = getBoardPosition(board, player->position);
    player->position = newPosition;
}

void renderPlayer(Player *player, SDL_Renderer *renderer) {
    // Render player as a circle on the board
    int radius = 10; // Radius of the circle

    // Calculate center of the circle based on player's position
    int centerX = (player->position % 10) * 80 + 40;
    int centerY = (player->position / 10) * 60 + 30;

    // Set render draw color to blue or red based on player index
    if (strncmp(player->name, "Player 1", sizeof("Player 1")) == 0) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
    } else if (strncmp(player->name, "Player 2", sizeof("Player 2")) == 0) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Default to black if unexpected player name
    }

    // Render filled circle for player
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}