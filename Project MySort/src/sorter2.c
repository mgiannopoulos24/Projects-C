#include "sorter.h"

void merge(Record *records, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Record *L = malloc(n1 * sizeof(Record));
    Record *R = malloc(n2 * sizeof(Record));

    for (int i = 0; i < n1; i++)
        L[i] = records[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = records[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].surname, R[j].surname) < 0 ||
           (strcmp(L[i].surname, R[j].surname) == 0 && strcmp(L[i].name, R[j].name) < 0) ||
           (strcmp(L[i].surname, R[j].surname) == 0 && strcmp(L[i].name, R[j].name) == 0 && L[i].id < R[j].id)) {
            records[k++] = L[i++];
        } else {
            records[k++] = R[j++];
        }
    }

    while (i < n1)
        records[k++] = L[i++];
    while (j < n2)
        records[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(Record *records, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(records, l, m);
        merge_sort(records, m + 1, r);
        merge(records, l, m, r);
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

    merge_sort(records, 0, count - 1);

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