#include <stdio.h>
#include <string.h>
#include "account.h"
#include "utilities.h"

Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

void createAccount() {
    Account newAccount;
    printf("Enter account number (up to %d characters): ", ACCOUNT_NUMBER_LENGTH - 1);
    scanf("%s", newAccount.accountNumber);
    printf("Enter customer name: ");
    scanf("%s", newAccount.customerName);
    newAccount.balance = 0.0;

    accounts[numAccounts++] = newAccount;
    printf("Account created successfully.\n");
}

Account* findAccountByNumber(const char* accNumber) {
    for (int i = 0; i < numAccounts; ++i) {
        if (strcmp(accounts[i].accountNumber, accNumber) == 0) {
            return &accounts[i];
        }
    }
    return NULL;
}

void deposit(Account* acc, float amount) {
    acc->balance += amount;
}

void withdraw(Account* acc, float amount) {
    if (acc->balance >= amount) {
        acc->balance -= amount;
    } else {
        printf("Insufficient balance.\n");
    }
}

void checkAmount() {
    char accNumber[ACCOUNT_NUMBER_LENGTH];
    printf("Enter account number: ");
    scanf("%s", accNumber);

    Account* acc = findAccountByNumber(accNumber);
    if (acc != NULL) {
        printf("Account Balance: %.2f\n", acc->balance);
    } else {
        printf("Account not found.\n");
    }
}
