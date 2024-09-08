#include <stdio.h>
#include <ctype.h>

// Συνάρτηση που μετατρέπει έναν δεκαεξαδικό χαρακτήρα σε ακέραιο
int hex_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';  // Αν ο χαρακτήρας είναι ψηφίο (0-9)
    if (c >= 'a' && c <= 'f') return c - 'a' + 10; // Αν ο χαρακτήρας είναι μικρό γράμμα (a-f)
    if (c >= 'A' && c <= 'F') return c - 'A' + 10; // Αν ο χαρακτήρας είναι κεφαλαίο γράμμα (A-F)
    return -1;  // Επιστρέφει -1 αν ο χαρακτήρας δεν είναι δεκαεξαδικός
}

int main() {
    int c;
    int high = -1, low;

    // Διαβάζουμε χαρακτήρες μέχρι να φτάσουμε στο τέλος της εισόδου (EOF)
    while ((c = getchar()) != EOF) {
        if (isxdigit(c)) { // Ελέγχουμε αν ο χαρακτήρας είναι δεκαεξαδικός
            if (high == -1) {
                high = hex_to_int(c); // Αποθηκεύουμε τον πρώτο δεκαεξαδικό χαρακτήρα
            } else {
                low = hex_to_int(c); // Αποθηκεύουμε τον δεύτερο δεκαεξαδικό χαρακτήρα
                // Συνδυάζουμε τους δύο χαρακτήρες για να σχηματίσουμε τον τελικό χαρακτήρα
                putchar((high << 4) | low);
                high = -1; // Επαναφέρουμε την τιμή του high για τον επόμενο ζεύγος χαρακτήρων
            }
        }
    }

    return 0;
}

// Μεταγλώττιση:
// gcc decode.c -o decode
// Δοκιμές:
// ./decode < encoded_message.txt