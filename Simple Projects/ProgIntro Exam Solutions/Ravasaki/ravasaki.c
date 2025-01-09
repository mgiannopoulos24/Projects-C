#include <stdio.h>
#include <string.h>

int main() {
    char line[1024];

    // Διαβάζουμε κάθε γραμμή από την πρότυπη είσοδο
    while (fgets(line, sizeof(line), stdin)) {
        // Αφαιρούμε τον χαρακτήρα νέας γραμμής, εάν υπάρχει
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Τυπώνουμε τη γραμμή και το "<3" με κόκκινο χρώμα
        printf("%s \033[31m<3\033[0m\n", line);
        // Ή αν προτιμάτε το emoji, αντικαταστήστε την παραπάνω printf με την παρακάτω
        // printf("%s \u2764\n", line);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc ravasaki.c -o ravasaki
// Δοκιμές:
// ./ravasaki < input.txt