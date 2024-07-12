#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100000

// Function to read DNA sequence from file
char* read_dna_sequence(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    char *sequence = (char*)malloc((MAX_LENGTH + 1) * sizeof(char));
    if (sequence == NULL) {
        fclose(file);
        return NULL;
    }
    
    int index = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF && index < MAX_LENGTH) {
        if (ch == 'A' || ch == 'G' || ch == 'T' || ch == 'C') {
            sequence[index++] = ch;
        }
    }
    sequence[index] = '\0';
    
    fclose(file);
    return sequence;
}

// Function to find the longest common substring using optimized dynamic programming
char* longest_common_substring(const char* s1, int len1, const char* s2, int len2) {
    int *prev = (int*)calloc((len2 + 1), sizeof(int));
    int *curr = (int*)calloc((len2 + 1), sizeof(int));

    int max_len = 0;
    int end_index = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
                if (curr[j] > max_len) {
                    max_len = curr[j];
                    end_index = i - 1;
                }
            } else {
                curr[j] = 0;
            }
        }
        int *temp = prev;
        prev = curr;
        curr = temp;
    }

    free(prev);
    free(curr);

    char* result = (char*)malloc((max_len + 1) * sizeof(char));
    strncpy(result, s1 + end_index - max_len + 1, max_len);
    result[max_len] = '\0';

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename1> <filename2>\n", argv[0]);
        return 1;
    }

    char* dna1 = read_dna_sequence(argv[1]);
    if (dna1 == NULL) {
        fprintf(stderr, "Error reading file %s\n", argv[1]);
        return 1;
    }

    char* dna2 = read_dna_sequence(argv[2]);
    if (dna2 == NULL) {
        fprintf(stderr, "Error reading file %s\n", argv[2]);
        free(dna1);
        return 1;
    }

    int len1 = strlen(dna1);
    int len2 = strlen(dna2);

    char* result = longest_common_substring(dna1, len1, dna2, len2);
    if (result != NULL) {
        printf("Maximum common substring is: %s\n", result);
        free(result);
    }

    free(dna1);
    free(dna2);
    
    return 0;
}