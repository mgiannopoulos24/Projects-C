#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define DATE_LENGTH 11

typedef struct {
    char name[50];
    char date_caught[DATE_LENGTH];
    int level;
} Pokemon;

// Συνάρτηση για σύγκριση ημερομηνιών (με βάση το φορμά "dd-mm-yyyy")
int compare_dates(const char *date1, const char *date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%d-%d-%d", &day1, &month1, &year1);
    sscanf(date2, "%d-%d-%d", &day2, &month2, &year2);

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Συνάρτηση για εκτύπωση Pokémon
void print_pokemon(const Pokemon *p) {
    printf("%s was caught on %s and is level %d\n", p->name, p->date_caught, p->level);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <date>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char *header = fgets(line, sizeof(line), file); // Διαβάζουμε και αγνοούμε την κεφαλίδα

    // Διαβάζουμε και αποθηκεύουμε τα Pokémon
    Pokemon pokemons[1000];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[50], date_caught[DATE_LENGTH];
        int level;

        // Παρουμε τα δεδομένα από κάθε γραμμή
        if (sscanf(line, "%49[^,], %10[^,], %d", name, date_caught, &level) == 3) {
            if (compare_dates(date_caught, argv[2]) >= 0) {
                strcpy(pokemons[count].name, name);
                strcpy(pokemons[count].date_caught, date_caught);
                pokemons[count].level = level;
                count++;
            }
        }
    }
    fclose(file);

    // Ταξινομούμε τα Pokémon με βάση την ημερομηνία
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (compare_dates(pokemons[i].date_caught, pokemons[j].date_caught) > 0) {
                Pokemon temp = pokemons[i];
                pokemons[i] = pokemons[j];
                pokemons[j] = temp;
            }
        }
    }

    // Εκτυπώνουμε τα αποτελέσματα
    for (int i = 0; i < count; i++) {
        print_pokemon(&pokemons[i]);
    }

    return 0;
}


// Μεταγλώττιση:
// gcc pokedex.c -o pokedex
// Εκτέλεση:
// ./pokedex pokedex.db 19-02-2024
// ./pokedex pokedex.db 01-01-2024