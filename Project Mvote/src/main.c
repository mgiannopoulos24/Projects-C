#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "inverted_list.h"
#include "commands.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s -f <registeredvoters> -b <bucketentries>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = NULL;
    int bucket_size = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "-b") == 0) {
            bucket_size = atoi(argv[++i]);
        }
    }

    if (!filename || bucket_size <= 0) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    HashTable *hash_table = create_hash_table(bucket_size);
    InvertedList *inverted_list = create_inverted_list(bucket_size);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    int pin, zip;
    char lname[50], fname[50];
    while (fscanf(file, "%d %s %s %d", &pin, lname, fname, &zip) != EOF) {
        Voter *voter = (Voter *) malloc(sizeof(Voter));
        voter->pin = pin;
        strcpy(voter->lname, lname);
        strcpy(voter->fname, fname);
        voter->zip = zip;
        voter->voted = 'N';
        insert_voter(hash_table, voter);
        insert_inverted_list(inverted_list, voter);
    }

    fclose(file);

    process_commands(hash_table, inverted_list);

    free_hash_table(hash_table);
    free_inverted_list(inverted_list);

    return EXIT_SUCCESS;
}
