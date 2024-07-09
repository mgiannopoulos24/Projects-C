#include "game.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void display_progress(const char *word, const int *guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed[i]) {
            printf("%c", word[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

int is_word_guessed(const int *guessed, int word_length) {
    for (int i = 0; i < word_length; i++) {
        if (!guessed[i]) {
            return 0;
        }
    }
    return 1;
}

void play_game(const char *word) {
    int word_length = strlen(word);
    int guessed[word_length];
    memset(guessed, 0, sizeof(guessed));

    int attempts_left = MAX_ATTEMPTS;
    char guessed_letters[26] = {0};
    int guessed_count = 0;

    printf("Welcome to Hangman!\n");

    while (attempts_left > 0) {
        printf("\nAttempts left: %d\n", attempts_left);
        display_progress(word, guessed);

        printf("Guessed letters: ");
        for (int i = 0; i < guessed_count; i++) {
            printf("%c ", guessed_letters[i]);
        }
        printf("\n");

        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (strchr(guessed_letters, guess)) {
            printf("You already guessed that letter.\n");
            continue;
        }

        guessed_letters[guessed_count++] = guess;

        int found = 0;
        for (int i = 0; i < word_length; i++) {
            if (word[i] == guess) {
                guessed[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            attempts_left--;
            printf("Wrong guess!\n");
        }

        if (is_word_guessed(guessed, word_length)) {
            printf("Congratulations! You've guessed the word: %s\n", word);
            return;
        }
    }

    printf("Sorry, you've run out of attempts. The word was: %s\n", word);
}
