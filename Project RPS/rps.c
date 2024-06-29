#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // for toupper() function

// Function to generate computer's choice
int generateComputerChoice() {
    // Generate a random number between 0 and 2
    return rand() % 3;
}

// Function to determine the winner
int determineWinner(int playerChoice, int opponentChoice) {
    // Rock: 0, Paper: 1, Scissors: 2
    // Returns: 0 if draw, 1 if player wins, -1 if opponent wins

    if (playerChoice == opponentChoice) {
        return 0; // Draw
    } else if ((playerChoice == 0 && opponentChoice == 2) ||
               (playerChoice == 1 && opponentChoice == 0) ||
               (playerChoice == 2 && opponentChoice == 1)) {
        return 1; // Player wins
    } else {
        return -1; // Opponent wins
    }
}

int main() {
    int player1Choice, player2Choice, computerChoice, result;
    char *choices[] = {"Rock", "Paper", "Scissors"};
    char playAgainst;

    // Seed the random number generator
    srand(time(NULL));

    printf("Welcome to Rock Paper Scissors!\n");
    printf("Do you want to play against the computer (C) or against another player (P)? Enter C or P: ");
    
    // Input validation loop for choosing opponent
    do {
        scanf(" %c", &playAgainst);
        playAgainst = toupper(playAgainst); // Convert to uppercase
        if (playAgainst != 'C' && playAgainst != 'P') {
            printf("Invalid choice. Please enter C or P: ");
        }
    } while (playAgainst != 'C' && playAgainst != 'P');

    // Game loop
    do {
        // Player 1's turn
        printf("\nPlayer 1's turn.\n");
        printf("Enter your choice:\n");
        printf("0 - Rock\n1 - Paper\n2 - Scissors\n");
        scanf("%d", &player1Choice);

        if (player1Choice < 0 || player1Choice > 2) {
            printf("Invalid choice. Please enter a number between 0 and 2.\n");
            continue;
        }

        // If playing against another player, get Player 2's choice
        if (playAgainst == 'P') {
            printf("\nPlayer 2's turn.\n");
            printf("Enter your choice:\n");
            printf("0 - Rock\n1 - Paper\n2 - Scissors\n");
            scanf("%d", &player2Choice);

            if (player2Choice < 0 || player2Choice > 2) {
                printf("Invalid choice. Please enter a number between 0 and 2.\n");
                continue;
            }
        } else { // playAgainst == 'C'
            // Generate computer's choice
            computerChoice = generateComputerChoice();
            printf("\nComputer's choice: %s\n", choices[computerChoice]);
        }

        // Determine and print the result
        if (playAgainst == 'P') {
            result = determineWinner(player1Choice, player2Choice);
            if (result == 0) {
                printf("It's a draw!\n");
            } else if (result == 1) {
                printf("Player 1 wins!\n");
            } else {
                printf("Player 2 wins!\n");
            }
        } else { // playAgainst == 'C'
            result = determineWinner(player1Choice, computerChoice);
            if (result == 0) {
                printf("It's a draw!\n");
            } else if (result == 1) {
                printf("You win against the computer!\n");
            } else {
                printf("Computer wins!\n");
            }
        }

        // Ask if the user wants to play again
        printf("\nDo you want to play again? Enter Y for yes or any other key to exit: ");
        scanf(" %c", &playAgainst); // Reusing playAgainst variable for play again decision
        playAgainst = toupper(playAgainst);
    } while (playAgainst == 'Y');

    printf("\nThank you for playing Rock Paper Scissors!\n");

    return 0;
}
