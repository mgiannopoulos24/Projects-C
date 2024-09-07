#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Συνάρτηση για να ελέγξει αν ο πίνακας είναι πολύτιμος
int is_precious(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int row_sums[rows];
    int col_sums[cols];
    int sum;

    // Υπολογισμός αθροισμάτων γραμμών
    for (int i = 0; i < rows; i++) {
        sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
        row_sums[i] = sum;
    }

    // Υπολογισμός αθροισμάτων στηλών
    for (int j = 0; j < cols; j++) {
        sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += matrix[i][j];
        }
        col_sums[j] = sum;
    }

    // Έλεγχος αν όλα τα αθροίσματα γραμμών είναι ίσα
    for (int i = 1; i < rows; i++) {
        if (row_sums[i] != row_sums[0]) {
            return 0;
        }
    }

    // Έλεγχος αν όλα τα αθροίσματα στηλών είναι ίσα
    for (int j = 1; j < cols; j++) {
        if (col_sums[j] != col_sums[0]) {
            return 0;
        }
    }

    // Έλεγχος αν τα αθροίσματα γραμμών και στηλών είναι ίσα
    if (row_sums[0] != col_sums[0]) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        fprintf(stderr, "Matrix size exceeds maximum allowed size\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    int matrix[MAX_SIZE][MAX_SIZE];

    // Ανάγνωση του πίνακα από το αρχείο
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    // Έλεγχος αν ο πίνακας είναι πολύτιμος
    if (is_precious(matrix, rows, cols)) {
        printf("My precious!\n");
    } else {
        printf("This matrix is NOT precious.\n");
    }

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc precious.c -o precious
// Εκτέλεση:
// ./precious ring.txt
// ./precious not-ring.txt