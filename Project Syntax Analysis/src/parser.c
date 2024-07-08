#include "parser.h"
#include <stdlib.h>
#include "lexer.h"
#include "ast.h"
#include <stdio.h>

static Token current_token;

static void advance_token() {
    current_token = get_next_token();
}

static ASTNode *factor();
static ASTNode *term();
static ASTNode *expr();

static ASTNode *factor() {
    Token token = current_token;

    if (token.type == TOKEN_INTEGER) {
        advance_token();
        return create_integer_node(token.value);
    } else if (token.type == TOKEN_LPAREN) {
        advance_token();
        ASTNode *node = expr();
        if (current_token.type != TOKEN_RPAREN) {
            return NULL; // Syntax error
        }
        advance_token();
        return node;
    }

    return NULL;  // Syntax error
}

static ASTNode *term() {
    ASTNode *node = factor();

    while (current_token.type == TOKEN_MULTIPLY || current_token.type == TOKEN_DIVIDE) {
        Token token = current_token;
        advance_token();
        ASTNode *right = factor();
        OperationType op;

        if (token.type == TOKEN_MULTIPLY) {
            op = OP_MULTIPLY;
        } else if (token.type == TOKEN_DIVIDE) {
            op = OP_DIVIDE;
        } else {
            return NULL; // Syntax error
        }

        node = create_binary_operation_node(op, node, right);
    }

    return node;
}

static ASTNode *expr() {
    ASTNode *node = term();

    while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
        Token token = current_token;
        advance_token();
        ASTNode *right = term();
        OperationType op;

        if (token.type == TOKEN_PLUS) {
            op = OP_ADD;
        } else if (token.type == TOKEN_MINUS) {
            op = OP_SUBTRACT;
        } else {
            return NULL; // Syntax error
        }

        node = create_binary_operation_node(op, node, right);
    }

    return node;
}

ASTNode *parse(const char *input) {
    init_lexer(input);
    advance_token();
    return expr();
}
