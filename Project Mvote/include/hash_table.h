#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "voter.h"

typedef struct HashNode {
    Voter *voter;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode **table;
    int size;
    int count;
} HashTable;

HashTable* create_hash_table(int size);
void free_hash_table(HashTable *hash_table);
int hash_function(int pin, int size);
Voter* search_voter(HashTable *hash_table, int pin);
void insert_voter(HashTable *hash_table, Voter *voter);
void write_voters_to_file(const char *filename, HashTable *hash_table);
void mark_voted(HashTable *hash_table, int pin);
void mark_voters_from_file(const char *filename, HashTable *hash_table);
int count_voted(HashTable *hash_table);
int count_total(HashTable *hash_table);
void list_all_voters(HashTable *hash_table);

#endif // HASH_TABLE_H