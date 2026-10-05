#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token create_token(TokenType type, const char *value) {
    Token token;

    token.type = type;

    if (value != NULL) {
        token.value = malloc(strlen(value) + 1);
        strcpy(token.value, value);
    } else {
        token.value = NULL;
    }

    return token;
}

void print_token(Token token) {
    printf("Token: ");

    switch (token.type) {
        case TOKEN_PRINT:
            printf("PRINT");
            break;

        case TOKEN_IDENTIFIER:
            printf("IDENTIFIER");
            break;

        case TOKEN_EQUALS:
            printf("EQUALS");
            break;

        case TOKEN_LEFT_PAREN:
            printf("LEFT_PAREN");
            break;

        case TOKEN_RIGHT_PAREN:
            printf("RIGHT_PAREN");
            break;

        case TOKEN_STRING:
            printf("STRING");
            break;

        case TOKEN_SEMICOLON:
            printf("SEMICOLON");
            break;

        case TOKEN_EOF:
            printf("EOF");
            break;
    }

    if (token.value != NULL) {
        printf(" -> %s", token.value);
    }

    printf("\n");
}

Token *tokenize(const char *source, int *count) {

    int capacity = 10;
    int token_count = 0;

    Token *tokens = malloc(sizeof(Token) * capacity);

    int i = 0;

    while (source[i] != '\0') {

        /* Ignore spaces */
        if (isspace(source[i])) {
            i++;
            continue;
        }

        /* Make sure there is enough space */
        if (token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * capacity);
        }

        /* print keyword */
        if (strncmp(&source[i], "print", 5) == 0 &&
            !isalnum(source[i + 5]) &&
            source[i + 5] != '_') {

            tokens[token_count++] =
                create_token(TOKEN_PRINT, "print");

            i += 5;
            continue;
        }

        /* Identifier */
        if (isalpha(source[i]) || source[i] == '_') {

            int start = i;

            while (isalnum(source[i]) || source[i] == '_') {
                i++;
            }

            int length = i - start;

            char *identifier = malloc(length + 1);

            strncpy(identifier, &source[start], length);
            identifier[length] = '\0';

            tokens[token_count++] =
                create_token(TOKEN_IDENTIFIER, identifier);

            free(identifier);

            continue;
        }

        /* Equals */
        if (source[i] == '=') {

            tokens[token_count++] =
                create_token(TOKEN_EQUALS, "=");

            i++;
            continue;
        }

        /* Left parenthesis */
        if (source[i] == '(') {

            tokens[token_count++] =
                create_token(TOKEN_LEFT_PAREN, "(");

            i++;
            continue;
        }

        /* Right parenthesis */
        if (source[i] == ')') {

            tokens[token_count++] =
                create_token(TOKEN_RIGHT_PAREN, ")");

            i++;
            continue;
        }

        /* Semicolon */
        if (source[i] == ';') {

            tokens[token_count++] =
                create_token(TOKEN_SEMICOLON, ";");

            i++;
            continue;
        }

        /* String */
        if (source[i] == '"') {

            i++;

            int start = i;

            while (source[i] != '"' && source[i] != '\0') {
                i++;
            }

            int length = i - start;

            char *string = malloc(length + 1);

            strncpy(string, &source[start], length);
            string[length] = '\0';

            tokens[token_count++] =
                create_token(TOKEN_STRING, string);

            free(string);

            if (source[i] == '"') {
                i++;
            }

            continue;
        }

        /* Unknown character */
        printf("Unknown character: %c\n", source[i]);

        i++;
    }

    tokens[token_count++] =
        create_token(TOKEN_EOF, NULL);

    *count = token_count;

    return tokens;
}
