#include "evaluator.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

int evaluate(ASTNode *root) {
    if (root == NULL) return 0;

    if (root->type == NODE_INTEGER) {
        return root->value;
    } else if (root->type == NODE_BINARY_OPERATION) {
        int left_value = evaluate(root->left);
        int right_value = evaluate(root->right);

        switch (root->op) {
            case OP_ADD:
                return left_value + right_value;
            case OP_SUBTRACT:
                return left_value - right_value;
            case OP_MULTIPLY:
                return left_value * right_value;
            case OP_DIVIDE:
                return left_value / right_value;
            default:
                return 0; // Invalid operation
        }
    }

    return 0; // Error
}
