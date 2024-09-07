#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 1000 // Το μέγιστο επίπεδο που θέλουμε να υποστηρίξουμε

// Συνάρτηση για υπολογισμό των διαφορετικών τρόπων για να φτάσουμε σε ένα επίπεδο
unsigned long long count_ways(int target_level) {
    if (target_level < 0) return 0; // Μη έγκυρο επίπεδο
    if (target_level == 0) return 1; // Υπάρχει μόνο ένας τρόπος για να φτάσουμε στο επίπεδο 0: να μην κάνουμε τίποτα

    // Δημιουργία πίνακα για την αποθήκευση των αποτελεσμάτων
    unsigned long long dp[MAX_LEVEL + 1] = {0};

    // Βασικές περιπτώσεις
    dp[0] = 1; // Υπάρχει 1 τρόπος να φτάσουμε στο επίπεδο 0

    for (int i = 1; i <= target_level; i++) {
        if (i >= 1) dp[i] += dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
        if (i >= 3) dp[i] += dp[i - 3];
    }

    return dp[target_level];
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_level>\n", argv[0]);
        return 1;
    }

    int target_level = atoi(argv[1]);
    if (target_level < 0) {
        fprintf(stderr, "The target level must be a non-negative integer.\n");
        return 1;
    }

    unsigned long long ways = count_ways(target_level);
    printf("There are %llu different ways to reach level %d\n", ways, target_level);

    return 0;
}

// Μεταγλώττιση:
// gcc levelup.c -o levelup
// Εκτέλεση:
// ./levelup 3
// ./levelup 5
// ./levelup 6
// ./levelup 50