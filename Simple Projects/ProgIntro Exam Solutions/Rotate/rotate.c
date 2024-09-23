#include <stdio.h>
#include <stdlib.h>

void rotate_matrix(int rows, int cols, int matrix[rows][cols]) {
    // Εκτυπώνουμε τον πίνακα περιστραμμένο κατά 90 μοίρες αντίστροφα
    for (int col = cols - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Μήνυμα λάθους αν δεν δοθεί το σωστό όρισμα
        fprintf(stderr, "Error: You must provide exactly one input file.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        // Μήνυμα λάθους αν δεν ανοίξει το αρχείο
        fprintf(stderr, "Error: Could not open the file.\n");
        return 1;
    }

    int rows, cols;

    // Διαβάζουμε τον αριθμό γραμμών και στηλών
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Error: Invalid file format.\n");
        fclose(file);
        return 1;
    }

    // Δημιουργούμε τον πίνακα δυναμικά
    int matrix[rows][cols];

    // Διαβάζουμε τα στοιχεία του πίνακα
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error: Invalid matrix data.\n");
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    // Περιστροφή και εκτύπωση του πίνακα
    rotate_matrix(rows, cols, matrix);

    return 0;
}

// Μεταγλώττιση:
// gcc rotate.c -o rotate
// Δοκιμές:
// ./rotate array.txt