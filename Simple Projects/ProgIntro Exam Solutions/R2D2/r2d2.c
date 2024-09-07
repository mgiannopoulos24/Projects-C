#include <stdio.h>
#include <stdlib.h>

// Συνάρτηση για την εκτέλεση XOR των bytes δύο αρχείων
void xor_files(FILE *file1, FILE *file2) {
    int byte1, byte2;

    // Διαβάστε bytes από τα δύο αρχεία μέχρι το τέλος του ενός από τα δύο αρχεία
    while ((byte1 = fgetc(file1)) != EOF && (byte2 = fgetc(file2)) != EOF) {
        // Υπολογίστε το XOR των δύο bytes
        int result = byte1 ^ byte2;
        // Εκτυπώστε το αποτέλεσμα ως χαρακτήρα
        printf("%c", result);
    }
}

int main(int argc, char *argv[]) {
    // Ελέγξτε αν έχουν δοθεί ακριβώς δύο ονόματα αρχείων
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Ανοίξτε τα αρχεία για ανάγνωση
    FILE *file1 = fopen(argv[1], "rb");
    FILE *file2 = fopen(argv[2], "rb");

    // Ελέγξτε αν τα αρχεία έχουν ανοιχτεί επιτυχώς
    if (!file1 || !file2) {
        perror("Error opening files");
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        return EXIT_FAILURE;
    }

    // Εκτελέστε το XOR για τα bytes των δύο αρχείων
    xor_files(file1, file2);

    // Κλείστε τα αρχεία
    fclose(file1);
    fclose(file2);

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc r2d2.c -o r2d2
// Εκτέλεση:
// ./r2d2 message.txt key.txt