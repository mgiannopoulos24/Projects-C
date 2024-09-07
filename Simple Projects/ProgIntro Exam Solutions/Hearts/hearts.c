#include <stdio.h>
#include <string.h>

// Συνάρτηση που ελέγχει αν μια συμβολοσειρά περιέχει ταιριαστές καρδιές
int is_matching_hearts(const char *arg) {
    int open_hearts = 0;

    // Διατρέχουμε κάθε χαρακτήρα της συμβολοσειράς
    for (int i = 0; i < strlen(arg); i++) {
        if (arg[i] == '<') {
            open_hearts++;  // Αύξηση του αριθμού των ανοιχτών καρδιών
        } else if (arg[i] == '3') {
            if (open_hearts == 0) {
                return 0;  // Βρέθηκε καρδιά που κλείνει χωρίς να έχει ανοίξει
            }
            open_hearts--;  // Μία καρδιά κλείνει
        } else {
            return 0;  // Άκυρος χαρακτήρας
        }
    }

    // Ελέγχουμε αν έχουν κλείσει όλες οι ανοιχτές καρδιές
    return open_hearts == 0;
}

int main(int argc, char *argv[]) {
    // Για κάθε όρισμα της γραμμής εντολών
    for (int i = 1; i < argc; i++) {
        // Εκτύπωση του ορίσματος και του αποτελέσματος
        printf("%s: %s\n", argv[i], is_matching_hearts(argv[i]) ? "yes" : "no");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc hearts.c -o hearts
// Δοκιμές:
// ./hearts '<3' '<.3>' '<<33' '<<<3' '<333' '<<33<3<<<<3<<33333'