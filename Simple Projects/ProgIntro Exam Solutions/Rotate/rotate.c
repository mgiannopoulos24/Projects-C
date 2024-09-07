#include <stdio.h>
#include <stdlib.h>

void rotate_matrix(int rows, int cols, int matrix[rows][cols]) {
    // Δημιουργούμε έναν πίνακα για την περιστροφή
    int rotated[cols][rows];

    // Γεμίζουμε τον νέο πίνακα με τα περιστραμμένα στοιχεία
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            rotated[c][rows - 1 - r] = matrix[r][c];
        }
    }

    // Εκτυπώνουμε τον περιστραμμένο πίνακα
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            printf("%d", rotated[c][r]);
            if (r < rows - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Error reading matrix dimensions\n");
        fclose(file);
        return 1;
    }

    // Δημιουργούμε τον πίνακα
    int matrix[rows][cols];

    // Διαβάζουμε τα στοιχεία του πίνακα από το αρχείο
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (fscanf(file, "%d", &matrix[r][c]) != 1) {
                fprintf(stderr, "Error reading matrix elements\n");
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    // Καλούμε τη συνάρτηση περιστροφής
    rotate_matrix(rows, cols, matrix);

    return 0;
}


// Μεταγλώττιση:
// gcc rotate.c -o rotate
// Δοκιμές:
// ./rotate array.txt