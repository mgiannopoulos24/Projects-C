#include <stdio.h>
#include "login.h"
#include "account.h"
#include "transaction.h"

void displayMainMenu();

int main() {
    int choice;
    initialize(); // Initialize any necessary data structures or setup

    while (1) {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Transfer Money
                performTransfer();
                break;
            case 2:
                // Create Account
                createAccount();
                break;
            case 3:
                // Check Amount
                checkAmount();
                break;
            case 4:
                // Login Functionality
                login();
                break;
            case 5:
                // Exit
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    }

    return 0;
}

void displayMainMenu() {
    printf("\n===== Main Menu =====\n");
    printf("1. Transfer Money\n");
    printf("2. Create Account\n");
    printf("3. Check Amount\n");
    printf("4. Login\n");
    printf("5. Exit\n");
}
