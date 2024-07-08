#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    int value;  // Only used if type is TOKEN_INTEGER
} Token;

void init_lexer(const char *input);
Token get_next_token();

#endif
