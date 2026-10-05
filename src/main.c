#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: h <file.he>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *source = malloc(file_size + 1);

    if (source == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    fread(source, 1, file_size, file);
    source[file_size] = '\0';

    fclose(file);

    /* 1. Lexer */
    int token_count = 0;
    Token *tokens = tokenize(source, &token_count);

    /* 2. Parser */
    parse_tokens(tokens, token_count);

    /* 3. Interpreter */
    printf("\n=== H Output ===\n\n");

    interpret(tokens, token_count);

    /* Cleanup */
    for (int i = 0; i < token_count; i++) {
        free(tokens[i].value);
    }

    free(tokens);
    free(source);

    return 0;
}
