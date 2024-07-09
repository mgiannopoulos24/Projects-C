#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "words.h"

int main() {
    srand(time(NULL));  // Seed the random number generator

    char word[MAX_WORD_LENGTH];
    if (!choose_random_word(word)) {
        printf("Failed to load word list.\n");
        return 1;
    }

    play_game(word);
    return 0;
}
