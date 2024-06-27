#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "utilities.h"

void performTransfer() {
    char fromAccount[ACCOUNT_NUMBER_LENGTH];
    char toAccount[ACCOUNT_NUMBER_LENGTH];
    float amount;

    printf("Enter sender's account number: ");
    scanf("%s", fromAccount);
    Account* sender = findAccountByNumber(fromAccount);
    if (sender == NULL) {
        printf("Sender account not found.\n");
        return;
    }

    printf("Enter recipient's account number: ");
    scanf("%s", toAccount);
    Account* recipient = findAccountByNumber(toAccount);
    if (recipient == NULL) {
        printf("Recipient account not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (sender->balance >= amount) {
        withdraw(sender, amount);
        deposit(recipient, amount);
        printf("Transfer successful.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}
