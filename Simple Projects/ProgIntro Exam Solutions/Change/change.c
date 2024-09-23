#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int width, height;

    // Έλεγχος για σωστή χρήση ορισμάτων
    if (argc != 2) {
        printf("Error: Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Άνοιγμα αρχείου εισόδου
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    // Ανάγνωση των διαστάσεων του γηπέδου
    if (fscanf(file, "%d %d", &height, &width) != 2) {
        printf("Error: Invalid file format\n");
        fclose(file);
        return 1;
    }

    // Δημιουργία πίνακα για την αποθήκευση των δεδομένων του γηπέδου
    int field[height][width];

    // Ανάγνωση των δεδομένων του γηπέδου
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (fscanf(file, "%d", &field[i][j]) != 1) {
                printf("Error: Invalid file format\n");
                fclose(file);
                return 1;
            }
        }
    }

    // Κλείσιμο του αρχείου εισόδου
    fclose(file);

    // Εκτύπωση του γηπέδου μετά από περιστροφή 180 μοιρών
    for (int i = height - 1; i >= 0; i--) {
        for (int j = width - 1; j >= 0; j--) {
            printf("%d ", field[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc change.c -o change
// Δοκιμές:
// ./change field.txt