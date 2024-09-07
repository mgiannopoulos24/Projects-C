#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Συνάρτηση για την αντικατάσταση των bytes στο αρχείο
void replace_bytes(const char *filename, long offset, uint16_t value) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Αποτυχία ανοίγματος αρχείου");
        exit(EXIT_FAILURE);
    }

    // Λήψη του μεγέθους του αρχείου
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Ανάγνωση ολόκληρου του αρχείου στη μνήμη
    uint8_t *buffer = malloc(filesize);
    if (!buffer) {
        perror("Αποτυχία κατανομής μνήμης");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, filesize, file);
    fclose(file);

    // Αντικατάσταση των bytes στη συγκεκριμένη θέση
    if (offset + 1 < filesize) {
        buffer[offset] = (value >> 8) & 0xFF; // Υψηλό byte
        buffer[offset + 1] = value & 0xFF;    // Χαμηλό byte
    } else {
        fprintf(stderr, "Η θέση είναι εκτός ορίων\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    // Εγγραφή του τροποποιημένου buffer στην πρότυπη έξοδο
    fwrite(buffer, 1, filesize, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Χρήση: %s <όνομα αρχείου> <θέση> <τιμή>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    long offset = strtol(argv[2], NULL, 10);
    uint16_t value = (uint16_t)strtol(argv[3], NULL, 10);

    replace_bytes(filename, offset, value);

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc crop.c -o crop
// Δοκιμές:
// ./crop rick.jpg 224 218 > rick2.jpg