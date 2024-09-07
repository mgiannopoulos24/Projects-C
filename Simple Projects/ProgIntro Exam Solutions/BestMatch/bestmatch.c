#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Δομή για να αποθηκεύσουμε τα ονόματα και τα σκορ τους
typedef struct {
    char name[100];
    float score;
} Person;

// Συνάρτηση σύγκρισης για να ταξινομήσουμε κατά φθίνουσα σειρά σκορ
int compare(const void *a, const void *b) {
    Person *personA = (Person *)a;
    Person *personB = (Person *)b;
    if (personB->score > personA->score)
        return 1;
    else if (personB->score < personA->score)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Πίνακας για να αποθηκεύσουμε τα άτομα
    Person people[100];
    int count = 0;

    // Διαβάζουμε το αρχείο και αποθηκεύουμε τα ονόματα και τα σκορ
    while (fscanf(file, "%[^,],%f\n", people[count].name, &people[count].score) != EOF) {
        count++;
    }

    fclose(file);

    // Ταξινόμηση του πίνακα κατά φθίνουσα σειρά σκορ
    qsort(people, count, sizeof(Person), compare);

    // Εκτύπωση των ταξινομημένων δεδομένων
    for (int i = 0; i < count; i++) {
        printf("%s,%.2f\n", people[i].name, people[i].score);
    }

    return 0;
}


// Μεταγλώττιση:
// gcc bestmatch.c -o bestmatch
// Δοκιμές:
// ./bestmatch names.txt