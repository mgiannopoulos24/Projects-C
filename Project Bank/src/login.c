#include <stdio.h>
#include <string.h>
#include "login.h"
#include "utilities.h"

#define MAX_USERS 10

typedef struct {
    char username[20];
    char password[20];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int numUsers = 2; // Number of predefined users

void initialize() {
    // Any initialization tasks if required
}

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void login() {
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed. Invalid credentials.\n");
    }
}
