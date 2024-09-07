#include <stdio.h>
#include <stdlib.h>

// Ο αριθμός των πρώτων bytes που πρέπει να διαβάσουμε για να ελέγξουμε αν είναι ELF
#define ELF_HEADER_SIZE 4

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    unsigned char header[ELF_HEADER_SIZE];
    size_t read_size = fread(header, 1, ELF_HEADER_SIZE, file);
    fclose(file);

    if (read_size != ELF_HEADER_SIZE) {
        printf("%s is NOT an ELF file.\n", argv[1]);
        return EXIT_SUCCESS;
    }

    // Ελέγχουμε αν το αρχείο ξεκινάει με τους χαρακτήρες 0x7f, 'E', 'L', 'F'
    if (header[0] == 0x7f && header[1] == 'E' && header[2] == 'L' && header[3] == 'F') {
        printf("%s is an ELF file.\n", argv[1]);
    } else {
        printf("%s is NOT an ELF file.\n", argv[1]);
    }

    return EXIT_SUCCESS;
}

// Μεταγλώττιση:
// gcc elf.c -o elf
// Εκτέλεση:
// ./elf /bin/ls
// ./elf ./elf.c
// ./elf ./elf
// ./elf /lib/x86_64-linux-gnu/libc.so.6