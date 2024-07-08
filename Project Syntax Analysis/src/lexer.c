#include "lexer.h"
#include <ctype.h>
#include <stdio.h>

static const char *input;
static int pos;
static int current_char;

void init_lexer(const char *input_text) {
    input = input_text;
    pos = 0;
    current_char = input[pos];
}

static void advance() {
    pos++;
    current_char = input[pos];
}

static Token create_token(TokenType type) {
    Token token;
    token.type = type;
    return token;
}

static Token error_token() {
    Token token;
    token.type = TOKEN_ERROR;
    return token;
}

Token get_next_token() {
    while (current_char != '\0') {
        if (isspace(current_char)) {
            advance();
            continue;
        }

        if (isdigit(current_char)) {
            int value = 0;
            while (isdigit(current_char)) {
                value = value * 10 + (current_char - '0');
                advance();
            }
            Token token;
            token.type = TOKEN_INTEGER;
            token.value = value;
            return token;
        }

        switch (current_char) {
            case '+':
                advance();
                return create_token(TOKEN_PLUS);
            case '-':
                advance();
                return create_token(TOKEN_MINUS);
            case '*':
                advance();
                return create_token(TOKEN_MULTIPLY);
            case '/':
                advance();
                return create_token(TOKEN_DIVIDE);
            case '(':
                advance();
                return create_token(TOKEN_LPAREN);
            case ')':
                advance();
                return create_token(TOKEN_RPAREN);
            default:
                return error_token();
        }
    }

    return create_token(TOKEN_END);
}
