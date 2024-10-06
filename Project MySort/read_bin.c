#include <stdio.h>
#include <stdlib.h>
#include "./include/mysort.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    Record record;
    printf("Contents of %s:\n", argv[1]);
    while (fread(&record, sizeof(Record), 1, file) == 1) {
        printf("ID: %d, Surname: %s, Name: %s, Zip: %s\n", record.id, record.surname, record.name, record.zip);
    }

    fclose(file);
    return 0;
}
