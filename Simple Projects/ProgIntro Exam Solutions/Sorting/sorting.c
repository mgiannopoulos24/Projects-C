#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 200

// Συνάρτηση για να αντιστοιχίσουμε το σκορ σε κοιτώνα
const char *get_house_name(float score) {
    if (score >= 1.0 && score < 2.0)
        return "Gryffindor";
    else if (score >= 2.0 && score < 3.0)
        return "Hufflepuff";
    else if (score >= 3.0 && score < 4.0)
        return "Ravenclaw";
    else if (score >= 4.0 && score <= 5.0)
        return "Slytherin";
    else
        return "Unknown"; // Για σκορ εκτός της καθορισμένης περιοχής
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

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char name[MAX_NAME_LENGTH];
        float score;
        
        // Ανάλυση της γραμμής
        if (sscanf(line, "%[^-] - %f", name, &score) == 2) {
            // Αφαίρεση των κενών και των ειδικών χαρακτήρων γύρω από το όνομα
            char *newline_pos = strchr(name, '\n');
            if (newline_pos) *newline_pos = '\0';
            
            // Εκτύπωση του αποτελέσματος
            printf("%s -> %s\n", name, get_house_name(score));
        } else {
            fprintf(stderr, "Error parsing line: %s", line);
        }
    }

    fclose(file);
    return 0;
}

// Μεταγλώττιση:
// gcc sorting.c -o sorting
// Δοκιμές:
// ./sorting names.txt