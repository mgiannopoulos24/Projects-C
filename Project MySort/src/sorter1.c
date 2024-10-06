#include "sorter.h"

void swap(Record *a, Record *b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Record *records, int low, int high) {
    Record pivot = records[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(records[j].surname, pivot.surname) < 0 || 
           (strcmp(records[j].surname, pivot.surname) == 0 && strcmp(records[j].name, pivot.name) < 0) ||
           (strcmp(records[j].surname, pivot.surname) == 0 && strcmp(records[j].name, pivot.name) == 0 && records[j].id < pivot.id)) {
            i++;
            swap(&records[i], &records[j]);
        }
    }
    swap(&records[i + 1], &records[high]);
    return i + 1;
}

void quicksort(Record *records, int low, int high) {
    if (low < high) {
        int pi = partition(records, low, high);
        quicksort(records, low, pi - 1);
        quicksort(records, pi + 1, high);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("fopen input");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("fopen output");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    Record records[MAX_RECORDS];
    int count = 0;

    while (fread(&records[count], sizeof(Record), 1, input) == 1) {
        count++;
    }

    printf("Before sorting:\n");
    for (int i = 0; i < count; i++) {
        printf("Record %d: ID=%d, Surname=%s, Name=%s, Zip=%s\n", i, records[i].id, records[i].surname, records[i].name, records[i].zip);
    }

    quicksort(records, 0, count - 1);

    printf("After sorting:\n");
    for (int i = 0; i < count; i++) {
        printf("Record %d: ID=%d, Surname=%s, Name=%s, Zip=%s\n", i, records[i].id, records[i].surname, records[i].name, records[i].zip);
    }

    for (int i = 0; i < count; i++) {
        fwrite(&records[i], sizeof(Record), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}