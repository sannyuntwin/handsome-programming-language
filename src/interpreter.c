#include <stdio.h>
#include <string.h>
#include "interpreter.h"

#define MAX_VARIABLES 100

typedef struct {
    char name[100];
    char value[200];
} Variable;

Variable variables[MAX_VARIABLES];
int variable_count = 0;

void set_variable(const char *name, const char *value) {

    strcpy(variables[variable_count].name, name);
    strcpy(variables[variable_count].value, value);

    variable_count++;
}

const char *get_variable(const char *name) {

    for (int i = 0; i < variable_count; i++) {

        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }

    return NULL;
}

void interpret(Token *tokens, int count) {

    int i = 0;

    while (i < count) {

        /* Variable assignment */
        if (tokens[i].type == TOKEN_IDENTIFIER) {

            if (i + 1 < count &&
                tokens[i + 1].type == TOKEN_EQUALS) {

                const char *name = tokens[i].value;

                i += 2;

                if (i < count &&
                    tokens[i].type == TOKEN_STRING) {

                    set_variable(name, tokens[i].value);

                    i++;

                }

                if (i < count &&
                    tokens[i].type == TOKEN_SEMICOLON) {

                    i++;
                }

                continue;
            }
        }

        /* print statement */
        if (tokens[i].type == TOKEN_PRINT) {

            i++;

            if (i < count &&
                tokens[i].type == TOKEN_LEFT_PAREN) {

                i++;
            }

            /* Print string */
            if (i < count &&
                tokens[i].type == TOKEN_STRING) {

                printf("%s\n", tokens[i].value);

                i++;
            }

            /* Print variable */
            else if (i < count &&
                     tokens[i].type == TOKEN_IDENTIFIER) {

                const char *value =
                    get_variable(tokens[i].value);

                if (value != NULL) {
                    printf("%s\n", value);
                } else {
                    printf("Undefined variable: %s\n",
                           tokens[i].value);
                }

                i++;
            }

            if (i < count &&
                tokens[i].type == TOKEN_RIGHT_PAREN) {

                i++;
            }

            if (i < count &&
                tokens[i].type == TOKEN_SEMICOLON) {

                i++;
            }

            continue;
        }

        i++;
    }
}