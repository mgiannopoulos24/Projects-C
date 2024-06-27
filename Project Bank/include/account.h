#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_ACCOUNTS 100
#define ACCOUNT_NUMBER_LENGTH 10

typedef struct {
    char accountNumber[ACCOUNT_NUMBER_LENGTH];
    char customerName[50];
    float balance;
} Account;

extern Account accounts[MAX_ACCOUNTS];
extern int numAccounts;

void createAccount();
Account* findAccountByNumber(const char* accNumber);
void deposit(Account* acc, float amount);
void withdraw(Account* acc, float amount);
void checkAmount();

#endif // ACCOUNT_H
