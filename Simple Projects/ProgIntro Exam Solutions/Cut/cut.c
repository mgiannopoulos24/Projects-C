#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 100 * 1024 * 1024  // Μέγιστο μέγεθος αρχείου 100MB

// Συνάρτηση για το κόψιμο των τελευταίων N bytes από το αρχείο
void cut_file(const char *filename, long bytes_to_cut) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    // Μετακίνηση δείκτη αρχείου στο τέλος του αρχείου
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Υπολογισμός νέου μεγέθους αρχείου
    long new_size = file_size - bytes_to_cut;
    if (new_size < 0) {
        fprintf(stderr, "Error: The number of bytes to cut is greater than the file size.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Ανάγνωση του αρχείου σε buffer
    char *buffer = (char *)malloc(new_size);
    if (!buffer) {
        perror("Unable to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Ανάγνωση των δεδομένων που πρέπει να κρατήσουμε
    fread(buffer, 1, new_size, file);
    fclose(file);

    // Εκτύπωση του νέου περιεχομένου στην πρότυπη έξοδο
    fwrite(buffer, 1, new_size, stdout);

    // Απελευθέρωση μνήμης
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <bytes_to_cut>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    long bytes_to_cut = atol(argv[2]);

    if (bytes_to_cut < 0) {
        fprintf(stderr, "Error: The number of bytes to cut must be non-negative.\n");
        return EXIT_FAILURE;
    }

    cut_file(filename, bytes_to_cut);

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc cut.c -o cut
// Εκτέλεση:
// ./cut msg.txt 6 > msg-cut.txt
// ./cut imperial.mp3 2256267 > imperial-cut.mp3