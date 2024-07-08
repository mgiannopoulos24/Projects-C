#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "evaluator.h"
#include "utils.h"

#define MAX_LINE_LENGTH 256

void evaluate_expression(const char *expression) {
    ASTNode *root = parse(expression);
    if (root == NULL) {
        error("Failed to parse expression");
    }

    int result = evaluate(root);
    printf("Arithmetic expression: %s\n", expression);
    printf("Result: %d\n", result);
    free_ast(root);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        char *newline_pos = strchr(line, '\n');
        if (newline_pos != NULL) {
            *newline_pos = '\0';
        }

        evaluate_expression(line);
    }

    fclose(file);
    return 0;
}
