#include <stdio.h>
#include <stdlib.h>

// Συνάρτηση για την ανάγνωση ενός πίνακα από ένα αρχείο
void read_matrix(const char *filename, float ***matrix, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Διαβάζουμε τις διαστάσεις του πίνακα
    if (fscanf(file, "%d %d", rows, cols) != 2) {
        fprintf(stderr, "Error reading matrix dimensions\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Δημιουργούμε το πίνακα
    *matrix = (float **)malloc(*rows * sizeof(float *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (float *)malloc(*cols * sizeof(float));
        for (int j = 0; j < *cols; j++) {
            if (fscanf(file, "%f", &(*matrix)[i][j]) != 1) {
                fprintf(stderr, "Error reading matrix data\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
}

// Συνάρτηση για την εκτύπωση ενός πίνακα
void print_matrix(float **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Συνάρτηση για τον υπολογισμό του γινομένου δύο πινάκων
void multiply_matrices(float **a, int a_rows, int a_cols, float **b, int b_rows, int b_cols, float ***result) {
    if (a_cols != b_rows) {
        fprintf(stderr, "Matrix dimensions do not match for multiplication\n");
        exit(EXIT_FAILURE);
    }

    // Δημιουργούμε τον πίνακα του αποτελέσματος
    *result = (float **)malloc(a_rows * sizeof(float *));
    for (int i = 0; i < a_rows; i++) {
        (*result)[i] = (float *)malloc(b_cols * sizeof(float));
        for (int j = 0; j < b_cols; j++) {
            (*result)[i][j] = 0.0;
            for (int k = 0; k < a_cols; k++) {
                (*result)[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <matrix1_file> <matrix2_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float **matrix1, **matrix2, **result;
    int m1_rows, m1_cols, m2_rows, m2_cols;

    // Διαβάζουμε τους δύο πίνακες
    read_matrix(argv[1], &matrix1, &m1_rows, &m1_cols);
    read_matrix(argv[2], &matrix2, &m2_rows, &m2_cols);

    // Υπολογίζουμε το γινόμενο των δύο πινάκων
    multiply_matrices(matrix1, m1_rows, m1_cols, matrix2, m2_rows, m2_cols, &result);

    // Εκτυπώνουμε το αποτέλεσμα
    print_matrix(result, m1_rows, m2_cols);

    // Ελευθερώνουμε τη μνήμη
    for (int i = 0; i < m1_rows; i++) free(matrix1[i]);
    free(matrix1);
    for (int i = 0; i < m2_rows; i++) free(matrix2[i]);
    free(matrix2);
    for (int i = 0; i < m1_rows; i++) free(result[i]);
    free(result);

    return EXIT_SUCCESS;
}


// Μεταγλώττιση:
// gcc mat_mult.c -o mat_mult
// Δοκιμές:
// ./mat_mult mat1.txt mat2.txt