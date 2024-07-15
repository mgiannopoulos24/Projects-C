#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "voter.h"

typedef struct HashNode {
    Voter *voter;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    int size;           // Current size of the hash table
    int initial_size;   // Initial size of the hash table
    int count;          // Number of elements stored in the hash table
    HashNode **table;   // Array of pointers to hash nodes
} HashTable;

HashTable* create_hash_table(int size);
void free_hash_table(HashTable *hash_table);
int hash_function(int pin, int size);
void insert_voter(HashTable *hash_table, Voter *voter);
Voter* search_voter(HashTable *hash_table, int pin);
void mark_voted(HashTable *hash_table, int pin);
int count_voted(HashTable *hash_table);
void list_all_voters(HashTable *hash_table);
void write_voters_to_file(const char *filename, HashTable *hash_table);
void mark_voters_from_file(const char *filename, HashTable *hash_table);
int count_total(HashTable *hash_table);

#endif // HASH_TABLE_H
