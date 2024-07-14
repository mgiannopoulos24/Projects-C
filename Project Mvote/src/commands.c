#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

void process_commands(HashTable *hash_table, InvertedList *inverted_list) {
    char command[256];
    while (1) {
        printf("mvote> ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "exit", 4) == 0) {
            break;
        } else if (strncmp(command, "l ", 2) == 0) {
            int pin;
            sscanf(command + 2, "%d", &pin);
            Voter *voter = search_voter(hash_table, pin);
            if (voter) {
                printf("%d %s %s %d %c\n", voter->pin, voter->lname, voter->fname, voter->zip, voter->voted);
            } else {
                printf("Voter not found\n");
            }
        } else if (strncmp(command, "i ", 2) == 0) {
            int pin, zip;
            char lname[50], fname[50];
            sscanf(command + 2, "%d %s %s %d", &pin, lname, fname, &zip);
            if (search_voter(hash_table, pin) != NULL) {
                printf("Voter with PIN %d already exists.\n", pin);
            } else {
                Voter *voter = (Voter *) malloc(sizeof(Voter));
                voter->pin = pin;
                strcpy(voter->lname, lname);
                strcpy(voter->fname, fname);
                voter->zip = zip;
                voter->voted = 'N';
                insert_voter(hash_table, voter);
                insert_inverted_list(inverted_list, voter);
                printf("Voter %d %s %s added.\n", pin, lname, fname);
                write_voters_to_file("registeredvoters.csv", hash_table);
            }
        } else if (strncmp(command, "m ", 2) == 0) {
            int pin;
            sscanf(command + 2, "%d", &pin);
            mark_voted(hash_table, pin);
            printf("Voter %d marked as voted.\n", pin);
            write_voters_to_file("registeredvoters.csv", hash_table);
        } else if (strncmp(command, "bv ", 3) == 0) {
            char filename[50];
            sscanf(command + 3, "%s", filename);
            mark_voters_from_file(filename, hash_table);
            write_voters_to_file("registeredvoters.csv", hash_table);
        } else if (strncmp(command, "v", 1) == 0) {
            int voted_count = count_voted(hash_table);
            printf("Voted: %d\n", voted_count);
        } else if (strncmp(command, "perc", 4) == 0) {
            int voted_count = count_voted(hash_table);
            int total_count = count_total(hash_table);
            printf("Percentage: %.2f%%\n", (float)voted_count / total_count * 100);
        } else if (strncmp(command, "z ", 2) == 0) {
            int zip;
            sscanf(command + 2, "%d", &zip);
            list_voters_by_zip(inverted_list, zip);
        } else if (strncmp(command, "o", 1) == 0) {
            display_postal_codes(inverted_list);
        } else if (strncmp(command, "list", 4) == 0) {
            list_all_voters(hash_table);
        } else {
            printf("Unknown command\n");
        }
    }
}
