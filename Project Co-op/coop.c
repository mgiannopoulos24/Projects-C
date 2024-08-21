#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define R 3   // Reward for mutual cooperation
#define P 1   // Payoff for mutual defection
#define T 5   // Temptation to defect
#define S 0   // Sucker's payoff

// Function prototypes
void play_game();

int main() {
    play_game();
    return 0;
}

// Function to play the game by reading moves from stdin and printing responses to stdout
void play_game() {
    char input[2];   // Buffer to read the opponent's move
    int player_move = 1; // Start with cooperate (1)
    int opponent_move = 1; // Start with cooperate (1)

    while (fgets(input, sizeof(input), stdin)) {
        // Strip newline character
        input[strcspn(input, "\n")] = 0;

        // Update opponent's move
        if (strcmp(input, "D") == 0) {
            opponent_move = 0; // Defect
        } else if (strcmp(input, "C") == 0) {
            opponent_move = 1; // Cooperate
        } else {
            printf("Invalid input. Use 'C' for cooperate or 'D' for defect.\n");
            continue;
        }

        // Determine player's move
        player_move = opponent_move; // Mimic opponent's last move

        // Print player's move
        if (player_move == 1) {
            printf("C\n");
        } else {
            printf("D\n");
        }
    }
}
