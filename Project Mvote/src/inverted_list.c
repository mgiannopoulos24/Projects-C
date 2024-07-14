#include <stdio.h>
#include <stdlib.h>
#include "inverted_list.h"

InvertedList* create_inverted_list(int size) {
    InvertedList *inverted_list = (InvertedList *) malloc(sizeof(InvertedList));
    inverted_list->size = size;
    inverted_list->table = (InvertedNode **) malloc(size * sizeof(InvertedNode *));
    for (int i = 0; i < size; i++) {
        inverted_list->table[i] = NULL;
    }
    return inverted_list;
}

void free_inverted_list(InvertedList *inverted_list) {
    for (int i = 0; i < inverted_list->size; i++) {
        InvertedNode *node = inverted_list->table[i];
        while (node) {
            InvertedNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(inverted_list->table);
    free(inverted_list);
}

void insert_inverted_list(InvertedList *inverted_list, Voter *voter) {
    int index = voter->zip % inverted_list->size;
    InvertedNode *new_node = (InvertedNode *) malloc(sizeof(InvertedNode));
    new_node->voter = voter;
    new_node->next = inverted_list->table[index];
    inverted_list->table[index] = new_node;
}

void list_voters_by_zip(InvertedList *inverted_list, int zip) {
    int index = zip % inverted_list->size;
    InvertedNode *node = inverted_list->table[index];
    while (node) {
        if (node->voter->zip == zip) {
            printf("%d %s %s %d %c\n", node->voter->pin, node->voter->lname, node->voter->fname, node->voter->zip, node->voter->voted);
        }
        node = node->next;
    }
}

int compare_zip_count(const void *a, const void *b) {
    ZipCount *za = (ZipCount *)a;
    ZipCount *zb = (ZipCount *)b;
    return zb->count - za->count; // Descending order
}

void display_postal_codes(InvertedList *inverted_list) {
    int capacity = 10;
    ZipCount *zip_count_array = (ZipCount *) malloc(capacity * sizeof(ZipCount));
    if (zip_count_array == NULL) {
        // Handle malloc failure
        fprintf(stderr, "Failed to allocate memory\n");
        return;
    }

    int unique_count = 0;

    for (int i = 0; i < inverted_list->size; i++) {
        InvertedNode *node = inverted_list->table[i];
        while (node) {
            if (node->voter->voted == 'Y') {
                int zip = node->voter->zip;
                int found = 0;
                for (int j = 0; j < unique_count; j++) {
                    if (zip_count_array[j].zip == zip) {
                        zip_count_array[j].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    if (unique_count >= capacity) {
                        capacity *= 2;
                        ZipCount *new_array = (ZipCount *) realloc(zip_count_array, capacity * sizeof(ZipCount));
                        if (new_array == NULL) {
                            // Handle realloc failure
                            free(zip_count_array);
                            fprintf(stderr, "Failed to reallocate memory\n");
                            return;
                        }
                        zip_count_array = new_array;
                    }
                    zip_count_array[unique_count].zip = zip;
                    zip_count_array[unique_count].count = 1;
                    unique_count++;
                }
            }
            node = node->next;
        }
    }

    qsort(zip_count_array, unique_count, sizeof(ZipCount), compare_zip_count);

    for (int i = 0; i < unique_count; i++) {
        printf("%d %d\n", zip_count_array[i].zip, zip_count_array[i].count);
    }

    free(zip_count_array);
}