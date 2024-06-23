#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000000

// Function to find the maximum common substring
void findMaxCommonSubstring(char* str1, char* str2, char* common_substring) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int max_len = 0;
    int end_index = 0;
    
    // Create a table to store lengths of longest common suffixes of substrings
    int **table = (int **)malloc((len1 + 1) * sizeof(int *));
    if (table == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < len1 + 1; i++) {
        table[i] = (int *)malloc((len2 + 1) * sizeof(int));
        if (table[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    
    // Initialize result
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            table[i][j] = 0;
        }
    }
    
    // Fill the table
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                if (table[i][j] > max_len) {
                    max_len = table[i][j];
                    end_index = i - 1;
                }
                // If we find a common substring that is as long as the entire sequences, we can exit early
                if (table[i][j] == len1 || table[i][j] == len2) {
                    max_len = table[i][j];
                    end_index = i - 1;
                    goto found; // Jump to label to exit loops early
                }
            }
            else {
                table[i][j] = 0;
            }
        }
    }
    
    found: // Label for early exit
    
    // Store the maximum common substring
    if (max_len > 0) {
        // Allocate exactly the necessary amount of memory for the common substring
        common_substring = realloc(common_substring, (max_len + 1) * sizeof(char));
        if (common_substring == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        int k = 0;
        for (int i = end_index - max_len + 1; i <= end_index; i++) {
            common_substring[k++] = str1[i];
        }
        common_substring[k] = '\0'; // Ensure proper string termination
    } else {
        strcpy(common_substring, "No common substring found.");
    }

    
    // Free dynamically allocated memory
    for (int i = 0; i < len1 + 1; i++) {
        free(table[i]);
    }
    free(table);
}

int main(int argc, char *argv[]) {
    // Check if two file names are provided as command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s filename1 filename2\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Open the files for reading
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    
    // Check if files are opened successfully
    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }
    
    // Read DNA sequences from files and filter out non-DNA characters
    char dna1[MAX_LENGTH];
    char dna2[MAX_LENGTH];

    int index1 = 0, index2 = 0;
    int c;

    while ((c = fgetc(file1)) != EOF && index1 < MAX_LENGTH - 1) {
        if (c == 'A' || c == 'G' || c == 'T' || c == 'C') {
            dna1[index1++] = (char)c;
        }
    }
    dna1[index1] = '\0';

    while ((c = fgetc(file2)) != EOF && index2 < MAX_LENGTH - 1) {
        if (c == 'A' || c == 'G' || c == 'T' || c == 'C') {
            dna2[index2++] = (char)c;
        }
    }
    dna2[index2] = '\0';
    
    // Close the files
    fclose(file1);
    fclose(file2);
    
    // Find the maximum common substring
    char *common_substring = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (common_substring == NULL) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    
    findMaxCommonSubstring(dna1, dna2, common_substring);
    //printf("Maximum common substring is: %s\n", common_substring); // Uncomment to print the common substring
    
    // Free dynamically allocated memory
    free(common_substring);
    
    return EXIT_SUCCESS;
}
