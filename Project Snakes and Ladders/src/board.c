#include "board.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initBoard(Board *board) {
    // Initialize snakes and ladders
    for (int i = 0; i <= 100; i++) {
        board->snakes[i] = i;
        board->ladders[i] = i;
    }
    // Example snakes
    board->snakes[16] = 6;
    board->snakes[47] = 26;
    board->snakes[49] = 11;
    board->snakes[56] = 53;
    board->snakes[62] = 19;
    board->snakes[64] = 60;
    board->snakes[87] = 24;
    board->snakes[93] = 73;
    board->snakes[95] = 75;
    board->snakes[98] = 78;

    // Example ladders
    board->ladders[1] = 38;
    board->ladders[4] = 14;
    board->ladders[9] = 31;
    board->ladders[21] = 42;
    board->ladders[28] = 84;
    board->ladders[36] = 44;
    board->ladders[51] = 67;
    board->ladders[71] = 91;
    board->ladders[80] = 100;
}

int getBoardPosition(Board *board, int position) {
    if (position > 100) return 100;
    if (board->snakes[position] != position) return board->snakes[position];
    if (board->ladders[position] != position) return board->ladders[position];
    return position;
}

void renderBoard(Board *board, SDL_Renderer *renderer, TTF_Font *font) {
    // Clear the board
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render grid lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= 10; i++) {
        SDL_RenderDrawLine(renderer, i * 80, 0, i * 80, 600);
        SDL_RenderDrawLine(renderer, 0, i * 60, 800, i * 60);
    }

    // Render numbers on board
    SDL_Color textColor = {0, 0, 0, 255};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int number = (i * 10) + j + 1;
            char numStr[4];
            sprintf(numStr, "%d", number);

            SDL_Surface *textSurface = TTF_RenderText_Solid(font, numStr, textColor);
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect renderQuad = {j * 80 + 10, i * 60 + 10, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

            SDL_DestroyTexture(textTexture);
            SDL_FreeSurface(textSurface);
        }
    }

    // Render snakes and ladders
    // Snakes - Green Color
    SDL_SetRenderDrawColor(renderer, 0, 122, 1, 255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable blending for thicker lines
    for (int i = 1; i <= 100; i++) {
        if (board->snakes[i] != i) {
            int startX = ((i - 1) % 10) * 80 + 40;
            int startY = ((i - 1) / 10) * 60 + 30;
            int endX = ((board->snakes[i] - 1) % 10) * 80 + 40;
            int endY = ((board->snakes[i] - 1) / 10) * 60 + 30;

            // Draw thicker snake lines
            SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
            SDL_RenderDrawLine(renderer, startX + 1, startY + 1, endX + 1, endY + 1); // Thickening effect
        }
    }

    // Ladders - Brown Color
    SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255);
    for (int i = 1; i <= 100; i++) {
        if (board->ladders[i] != i) {
            int startX = ((i - 1) % 10) * 80 + 40;
            int startY = ((i - 1) / 10) * 60 + 30;
            int endX = ((board->ladders[i] - 1) % 10) * 80 + 40;
            int endY = ((board->ladders[i] - 1) / 10) * 60 + 30;

            // Draw thicker ladder lines
            SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
            SDL_RenderDrawLine(renderer, startX + 1, startY + 1, endX + 1, endY + 1); // Thickening effect
        }
    }

    // Present the render
    SDL_RenderPresent(renderer);
}