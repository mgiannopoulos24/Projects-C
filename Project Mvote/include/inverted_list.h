#ifndef INVERTED_LIST_H
#define INVERTED_LIST_H

#include "voter.h"

typedef struct InvertedNode {
    Voter *voter;
    struct InvertedNode *next;
    struct InvertedNode *prev;
} InvertedNode;

typedef struct InvertedList {
    int size;
    InvertedNode **table;
} InvertedList;

typedef struct ZipCount {
    int zip;
    int count;
} ZipCount;

InvertedList* create_inverted_list(int size);
void free_inverted_list(InvertedList *inverted_list);
void insert_inverted_list(InvertedList *inverted_list, Voter *voter);
void list_voters_by_zip(InvertedList *inverted_list, int zip);
void display_postal_codes(InvertedList *inverted_list);

#endif // INVERTED_LIST_H