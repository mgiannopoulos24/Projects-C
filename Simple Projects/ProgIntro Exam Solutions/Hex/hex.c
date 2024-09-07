#include <stdio.h>

int main() {
    unsigned char buffer[16];
    int count;
    int i;

    // Διαβάζουμε μέχρι 16 χαρακτήρες από την είσοδο
    while ((count = fread(buffer, 1, 16, stdin)) > 0) {
        // Τυπώνουμε κάθε χαρακτήρα σε δεκαεξαδική μορφή
        for (i = 0; i < count; i++) {
            printf("%02x ", buffer[i]);
        }
        // Αν δεν έχουμε συμπληρώσει 16 χαρακτήρες, τυπώνουμε κενές θέσεις
        for (i = count; i < 16; i++) {
            printf("   "); // Κενές θέσεις για το padding
        }
        printf("\n"); // Νέα γραμμή μετά από κάθε ομάδα 16 χαρακτήρων
    }

    return 0;
}

// Μεταγλώττιση:
// gcc hex.c -o hex
// Δοκιμές:
// ./hex < domo.txt