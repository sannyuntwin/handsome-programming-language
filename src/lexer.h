#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_PRINT,
    TOKEN_IDENTIFIER,
    TOKEN_EQUALS,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token create_token(TokenType type, const char *value);
void print_token(Token token);

Token *tokenize(const char *source, int *count);

#endif