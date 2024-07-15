#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Helper function declarations
void resize_hash_table(HashTable *hash_table);

HashTable* create_hash_table(int size) {
    HashTable *hash_table = (HashTable *) malloc(sizeof(HashTable));
    if (hash_table == NULL) {
        perror("Failed to allocate memory for hash table");
        return NULL;
    }

    hash_table->size = size;
    hash_table->initial_size = size;
    hash_table->count = 0;
    hash_table->table = (HashNode **) malloc(size * sizeof(HashNode *));
    if (hash_table->table == NULL) {
        perror("Failed to allocate memory for hash table array");
        free(hash_table);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }

    return hash_table;
}

void free_hash_table(HashTable *hash_table) {
    if (hash_table == NULL) {
        return;
    }

    for (int i = 0; i < hash_table->size; i++) {
        HashNode *node = hash_table->table[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->voter);
            free(temp);
        }
    }

    free(hash_table->table);
    free(hash_table);
}

int hash_function(int pin, int size) {
    return pin % size;
}

void insert_voter(HashTable *hash_table, Voter *voter) {
    // Check load factor and resize if necessary
    if ((float) hash_table->count / hash_table->size > 0.75) {
        resize_hash_table(hash_table);
    }

    int index = hash_function(voter->pin, hash_table->size);
    HashNode *new_node = (HashNode *) malloc(sizeof(HashNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        return;
    }
    new_node->voter = voter;
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;
    hash_table->count++;
}

Voter* search_voter(HashTable *hash_table, int pin) {
    int index = hash_function(pin, hash_table->size);
    HashNode *node = hash_table->table[index];
    while (node) {
        if (node->voter->pin == pin) {
            return node->voter;
        }
        node = node->next;
    }
    return NULL;
}

void mark_voted(HashTable *hash_table, int pin) {
    Voter *voter = search_voter(hash_table, pin);
    if (voter) {
        voter->voted = 'Y';
    }
}

int count_voted(HashTable *hash_table) {
    int count = 0;
    for (int i = 0; i < hash_table->size; i++) {
        HashNode *node = hash_table->table[i];
        while (node) {
            if (node->voter->voted == 'Y') {
                count++;
            }
            node = node->next;
        }
    }
    return count;
}

void list_all_voters(HashTable *hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        HashNode *node = hash_table->table[i];
        while (node) {
            Voter *voter = node->voter;
            printf("%d %s %s %d %c\n", voter->pin, voter->lname, voter->fname, voter->zip, voter->voted);
            node = node->next;
        }
    }
}

void write_voters_to_file(const char *filename, HashTable *hash_table) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < hash_table->size; i++) {
        HashNode *node = hash_table->table[i];
        while (node) {
            Voter *voter = node->voter;
            fprintf(file, "%d %s %s %d %c\n", voter->pin, voter->lname, voter->fname, voter->zip, voter->voted);
            node = node->next;
        }
    }

    fclose(file);
}

void mark_voters_from_file(const char *filename, HashTable *hash_table) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int pin;
        int matched = sscanf(line, "%d", &pin);
        if (matched == 1) {
            printf("Processing PIN: %d\n", pin);  // Debug print
            mark_voted(hash_table, pin);
        } else {
            printf("Failed to read PIN from line: %s", line);
        }
    }

    fclose(file);
}

int count_total(HashTable *hash_table) {
    return hash_table->count;
}

void resize_hash_table(HashTable *hash_table) {
    int new_size = hash_table->size * 2;
    HashNode **new_table = (HashNode **) malloc(new_size * sizeof(HashNode *));
    if (new_table == NULL) {
        perror("Failed to allocate memory for new hash table array");
        return;
    }

    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    // Rehash all existing elements into the new table
    for (int i = 0; i < hash_table->size; i++) {
        HashNode *node = hash_table->table[i];
        while (node) {
            HashNode *next = node->next;
            int index = hash_function(node->voter->pin, new_size);
            node->next = new_table[index];
            new_table[index] = node;
            node = next;
        }
    }

    free(hash_table->table);
    hash_table->table = new_table;
    hash_table->size = new_size;
}
