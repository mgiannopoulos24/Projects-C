#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h> // for log2 function
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 700 // Increased height to accommodate the score box
#define TILE_SIZE 100
#define BORDER_SIZE 10 // Adjust border thickness as needed

SDL_Texture *load_texture_from_text(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color);
void render_board(SDL_Renderer *renderer, int board[4][4], int score, TTF_Font *font, SDL_Color color);

int main() {
    int board[4][4] = {0};
    int score = 0;

    srand(time(NULL));
    init_game(board);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("2048", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Load font from the src directory
    char font_path[256];  // Adjust size as necessary
    snprintf(font_path, sizeof(font_path), "%s%s", "src/", "arial.ttf");
    TTF_Font *font = TTF_OpenFont(font_path, 36);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Color color = {0, 0, 0, 255};  // Text color (black)

    // Main game loop
    int quit = 0;
    while (!quit && !is_game_over(board)) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1; // Set quit flag to exit the loop
            }
            if (e.type == SDL_KEYDOWN) {
                char move = ' ';
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        move = 'w';
                        break;
                    case SDLK_a:
                        move = 'a';
                        break;
                    case SDLK_s:
                        move = 's';
                        break;
                    case SDLK_d:
                        move = 'd';
                        break;
                }

                if (move == 'w' || move == 'a' || move == 's' || move == 'd') {
                    if (make_move(board, move, &score)) {
                        add_new_element(board);
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render the score box on the top-right corner
        char score_text[32];
        snprintf(score_text, sizeof(score_text), "Score: %d", score);
        SDL_Texture *score_texture = load_texture_from_text(renderer, score_text, font, color);
        if (score_texture != NULL) {
            int texW = 0, texH = 0;
            SDL_QueryTexture(score_texture, NULL, NULL, &texW, &texH);
            SDL_Rect score_rect = {WINDOW_WIDTH - texW - 20, 20, texW, texH}; // Adjust position as needed
            SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
            SDL_DestroyTexture(score_texture);
        }

        render_board(renderer, board, score, font, color);

        SDL_RenderPresent(renderer);

        usleep(100000); // Delay to make the game speed reasonable
    }

    // Cleanup
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    printf("Game Over!\n");
    printf("Final Score: %d\n", score);

    return 0;
}

void render_board(SDL_Renderer *renderer, int board[4][4], int score, TTF_Font *font, SDL_Color color) {
    // Define colors for numbers
    SDL_Color number_colors[12]; // Adjust size to accommodate all potential values

    SDL_Color color_2 = {238, 228, 218, 255};      // 2 (light ochre)
    SDL_Color color_4 = {237, 224, 200, 255};      // 4 (darker ochre)
    SDL_Color color_8 = {242, 177, 121, 255};      // 8 (light orange)
    SDL_Color color_16 = {245, 149, 99, 255};      // 16 (slightly darker orange)
    SDL_Color color_32 = {246, 124, 95, 255};      // 32 (even darker orange)
    SDL_Color color_64 = {228, 103, 71, 255};      // 64 (final dark orange)
    SDL_Color color_128 = {234, 209, 127, 255};    // 128 (first yellow)
    SDL_Color color_256 = {232, 205, 113, 255};    // 256 (second yellow)
    SDL_Color color_512 = {236, 199, 80, 255};     // 512 (third yellow)
    SDL_Color color_1024 = {233, 198, 63, 255};    // 1024 (fourth yellow)
    SDL_Color color_2048 = {234, 195, 49, 255};    // 2048 (final yellow)

    // Assign colors to the array indices
    number_colors[0] = color;     // 0 (should not be visible)
    number_colors[1] = color_2;
    number_colors[2] = color_4;
    number_colors[3] = color_8;
    number_colors[4] = color_16;
    number_colors[5] = color_32;
    number_colors[6] = color_64;
    number_colors[7] = color_128;
    number_colors[8] = color_256;
    number_colors[9] = color_512;
    number_colors[10] = color_1024;
    number_colors[11] = color_2048;

    // Calculate total width and height for the board including borders
    int board_width = 4 * (TILE_SIZE + BORDER_SIZE) + BORDER_SIZE;
    int board_height = 4 * (TILE_SIZE + BORDER_SIZE) + BORDER_SIZE;

    // Draw background for the entire board
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255); // Board background color
    SDL_Rect board_rect = { (WINDOW_WIDTH - board_width) / 2, (WINDOW_HEIGHT - board_height) / 2, board_width, board_height };
    SDL_RenderFillRect(renderer, &board_rect);

    // Render each tile and number
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Calculate tile position and size
            SDL_Rect tile;
            tile.x = (WINDOW_WIDTH - board_width) / 2 + BORDER_SIZE + j * (TILE_SIZE + BORDER_SIZE);
            tile.y = (WINDOW_HEIGHT - board_height) / 2 + BORDER_SIZE + i * (TILE_SIZE + BORDER_SIZE);
            tile.w = TILE_SIZE;
            tile.h = TILE_SIZE;

            // Draw tile color based on value
            SDL_Color tile_color = {205, 193, 180, 255}; // Default tile color
            if (board[i][j] > 0) {
                int value = board[i][j];
                int index = 0;
                while (value > 1) {
                    value /= 2;
                    index++;
                }
                if (index >= 1 && index < 12) {
                    tile_color = number_colors[index];
                }
            }
            SDL_SetRenderDrawColor(renderer, tile_color.r, tile_color.g, tile_color.b, tile_color.a);
            SDL_RenderFillRect(renderer, &tile);

            // Render number if tile is not empty
            if (board[i][j] != 0) {
                char text[8];  // Buffer for number text
                sprintf(text, "%d", board[i][j]);  // Convert number to text

                SDL_Texture *number_texture = load_texture_from_text(renderer, text, font, color);
                if (number_texture != NULL) {
                    int texW = 0, texH = 0;
                    SDL_QueryTexture(number_texture, NULL, NULL, &texW, &texH);
                    SDL_Rect dstRect = { tile.x + (TILE_SIZE - texW) / 2, tile.y + (TILE_SIZE - texH) / 2, texW, texH };
                    SDL_RenderCopy(renderer, number_texture, NULL, &dstRect);
                    SDL_DestroyTexture(number_texture);
                }
            }
        }
    }

}

SDL_Texture *load_texture_from_text(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color) {
    SDL_Surface *surf = TTF_RenderText_Blended(font, text, color);
    if (surf == NULL) {
        printf("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

void print_score(int score) {
    printf("Score: %d\n", score);
}
