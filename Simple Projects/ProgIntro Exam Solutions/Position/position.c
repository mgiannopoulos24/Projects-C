#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIMENSION 100

int main(int argc, char *argv[]) {
    // Έλεγχος αν υπάρχουν αρκετά ορίσματα
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dimension> [<ghost_x>,<ghost_y> ...]\n", argv[0]);
        return 1;
    }

    // Παρσάρισμα της διάστασης του πλέγματος
    int dimension = atoi(argv[1]);
    if (dimension <= 0 || dimension > MAX_DIMENSION) {
        fprintf(stderr, "Error: Invalid dimension '%s'\n", argv[1]);
        return 1;
    }

    // Πίνακες για τις κατειλημμένες σειρές και στήλες
    int occupied_rows[MAX_DIMENSION] = {0};
    int occupied_cols[MAX_DIMENSION] = {0};

    // Παρσάρισμα των θέσεων των φαντασμάτων
    for (int i = 2; i < argc; i++) {
        int x, y;
        if (sscanf(argv[i], "%d,%d", &x, &y) != 2) {
            fprintf(stderr, "Error: Invalid ghost position '%s'\n", argv[i]);
            return 1;
        }
        // Δεν ελέγχουμε αν οι συντεταγμένες των φαντασμάτων είναι εντός πλέγματος
        if (x >= 0 && x < MAX_DIMENSION)
            occupied_cols[x] = 1;
        if (y >= 0 && y < MAX_DIMENSION)
            occupied_rows[y] = 1;
    }

    // Εύρεση των διαθέσιμων θέσεων για τον Pacman
    int found = 0;
    for (int x = 0; x < dimension; x++) {
        if (occupied_cols[x])
            continue;
        for (int y = 0; y < dimension; y++) {
            if (occupied_rows[y])
                continue;
            // Βρέθηκε διαθέσιμη θέση
            if (!found) {
                printf("Pacman can be positioned at: %d,%d\n", x, y);
                found = 1;
            } else {
                printf("Pacman can be positioned at: %d,%d\n", x, y);
            }
        }
    }

    // Αν δεν βρέθηκε καμία διαθέσιμη θέση
    if (!found) {
        printf("Pacman cannot be positioned anywhere\n");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc position.c -o position
// Εκτέλεση:
// ./position 4 0,4 3,2 2,1 1,3
// ./position 4 0,4 3,2 2,1 0,3
// ./position 4 0,4 3,2 2,1
// ./position 4 1,2 2,1