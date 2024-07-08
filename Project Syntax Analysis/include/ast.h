#ifndef AST_H
#define AST_H

typedef enum {
    NODE_INTEGER,
    NODE_BINARY_OPERATION
} NodeType;

typedef enum {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} OperationType;

typedef struct ASTNode {
    NodeType type;
    union {
        int value;  // For NODE_INTEGER
        struct {
            OperationType op;
            struct ASTNode *left;
            struct ASTNode *right;
        };  // For NODE_BINARY_OPERATION
    };
} ASTNode;

ASTNode *create_integer_node(int value);
ASTNode *create_binary_operation_node(OperationType op, ASTNode *left, ASTNode *right);
void free_ast(ASTNode *node);

#endif
