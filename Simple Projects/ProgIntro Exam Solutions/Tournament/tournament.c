#include <stdio.h>

int main(int argc, char *argv[]) {
    // Ελέγχουμε αν έχουμε τουλάχιστον 3 Pokémon ως ορίσματα
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pokemon1> <pokemon2> ...\n", argv[0]);
        return 1;
    }

    // Για κάθε ζεύγος Pokémon, εκτυπώνουμε τις αντιπαραθέσεις
    for (int i = 1; i < argc; i++) {
        for (int j = i + 1; j < argc; j++) {
            // Εκτυπώνουμε και τις δύο πιθανές αντιπαραθέσεις
            printf("%s vs %s\n", argv[i], argv[j]);
            printf("%s vs %s\n", argv[j], argv[i]);
        }
    }

    return 0;
}


// Μεταγλώττιση:
// gcc tournament.c -o tournament
// Εκτέλεση:
// ./tournament Pikachu Charmander Bulbasaur