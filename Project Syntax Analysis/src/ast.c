#include "ast.h"
#include <stdlib.h>

ASTNode *create_integer_node(int value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_INTEGER;
    node->value = value;
    return node;
}

ASTNode *create_binary_operation_node(OperationType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OPERATION;
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;

    if (node->type == NODE_BINARY_OPERATION) {
        free_ast(node->left);
        free_ast(node->right);
    }

    free(node);
}
