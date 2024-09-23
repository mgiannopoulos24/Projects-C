#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 128
#define MAX_WORD_LEN 128

// Συνάρτηση για να διαχωρίσει μια πρόταση σε λέξεις
int split_sentence(char *sentence, char words[MAX_WORDS][MAX_WORD_LEN]) {
    int count = 0;
    char *token = strtok(sentence, " ");
    
    while (token != NULL && count < MAX_WORDS) {
        strncpy(words[count], token, MAX_WORD_LEN - 1);
        words[count][MAX_WORD_LEN - 1] = '\0';  // Διασφαλίζουμε ότι το string είναι null-terminated
        count++;
        token = strtok(NULL, " ");
    }
    
    return count;
}

// Συνάρτηση για να ελέγξει αν οι προτάσεις μπορούν να μεταμορφωθούν
int can_metamorphose(char words1[MAX_WORDS][MAX_WORD_LEN], char words2[MAX_WORDS][MAX_WORD_LEN], int word_count) {
    char map1[MAX_WORDS][MAX_WORD_LEN]; // Χάρτης λέξεων από πρόταση 1 σε πρόταση 2
    char map2[MAX_WORDS][MAX_WORD_LEN]; // Χάρτης λέξεων από πρόταση 2 σε πρόταση 1
    int map_count = 0;

    for (int i = 0; i < word_count; i++) {
        int found1 = -1, found2 = -1;
        // Έλεγχος αν η λέξη έχει ήδη αντιστοιχιστεί
        for (int j = 0; j < map_count; j++) {
            if (strcmp(words1[i], map1[j]) == 0) {
                found1 = j;
            }
            if (strcmp(words2[i], map2[j]) == 0) {
                found2 = j;
            }
        }
        
        // Αν μία λέξη από την πρώτη πρόταση έχει αντιστοιχιστεί σε διαφορετική λέξη, δεν είναι δυνατή η μεταμόρφωση
        if ((found1 != -1 && strcmp(words2[i], map2[found1]) != 0) || 
            (found2 != -1 && strcmp(words1[i], map1[found2]) != 0)) {
            return 0;
        }
        
        // Αν δεν έχει αντιστοιχιστεί, προσθέτουμε την αντιστοίχιση
        if (found1 == -1 && found2 == -1) {
            strncpy(map1[map_count], words1[i], MAX_WORD_LEN - 1);
            strncpy(map2[map_count], words2[i], MAX_WORD_LEN - 1);
            map1[map_count][MAX_WORD_LEN - 1] = '\0';
            map2[map_count][MAX_WORD_LEN - 1] = '\0';
            map_count++;
        }
    }
    
    // Επιστρέφουμε επιτυχία
    return 1;
}

// Συνάρτηση για να εκτυπώσει τις αντιστοιχίσεις
void print_mappings(char words1[MAX_WORDS][MAX_WORD_LEN], char words2[MAX_WORDS][MAX_WORD_LEN], int word_count) {
    for (int i = 0; i < word_count; i++) {
        printf("%s <-> %s\n", words1[i], words2[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // Ελέγχει αν δίνονται ακριβώς 2 προτάσεις ως είσοδος
        fprintf(stderr, "Error: You must provide exactly two sentences.\n");
        return 1;
    }

    char words1[MAX_WORDS][MAX_WORD_LEN];
    char words2[MAX_WORDS][MAX_WORD_LEN];
    
    // Δημιουργία αντιγράφων των προτάσεων για χρήση με strtok
    char sentence1_copy[strlen(argv[1]) + 1];
    char sentence2_copy[strlen(argv[2]) + 1];
    strcpy(sentence1_copy, argv[1]);
    strcpy(sentence2_copy, argv[2]);

    // Διαχωρισμός των προτάσεων σε λέξεις
    int word_count1 = split_sentence(sentence1_copy, words1);
    int word_count2 = split_sentence(sentence2_copy, words2);

    // Έλεγχος αν οι δύο προτάσεις έχουν τον ίδιο αριθμό λέξεων
    if (word_count1 != word_count2) {
        printf("You cannot metamorphose the first sentence into the second sentence\n");
        return 1;
    }

    // Έλεγχος αν μπορούμε να μεταμορφώσουμε τη μία πρόταση στην άλλη
    if (can_metamorphose(words1, words2, word_count1)) {
        printf("You can metamorphose the first sentence into the second sentence\n");
        print_mappings(words1, words2, word_count1);
    } else {
        printf("You cannot metamorphose the first sentence into the second sentence\n");
    }

    return 0;
}

// Μεταγλώττιση:
// gcc meta.c -o meta
// Δοκιμές:
// ./meta "I solemnly swear I am up to no good" "Magic glimmers brightly Magic creatures stand under the moonlight"
// ./meta "I solemnly swear I am up to no good" "Magic glimmers brightly magic creatures stand under the moonlight"