#include <stdio.h>
#include "parser.h"

void parse_tokens(Token *tokens, int count) {

    int i = 0;

    while (i < count) {

        /* Variable assignment:
           name = "San";
        */
        if (tokens[i].type == TOKEN_IDENTIFIER) {

            if (i + 1 < count &&
                tokens[i + 1].type == TOKEN_EQUALS) {

                printf("Parser found variable assignment: %s\n",
                       tokens[i].value);

                i += 2;

                if (i < count &&
                    tokens[i].type == TOKEN_STRING) {

                    printf("Parser found value: %s\n",
                           tokens[i].value);

                    i++;

                } else {
                    printf("Parser error: expected value\n");
                    return;
                }

                if (i < count &&
                    tokens[i].type == TOKEN_SEMICOLON) {

                    i++;

                } else {
                    printf("Parser error: expected ';'\n");
                    return;
                }

                printf("Parser: valid variable assignment!\n\n");

                continue;
            }
        }

        /* print statement */
        if (tokens[i].type == TOKEN_PRINT) {

            printf("Parser found PRINT statement\n");

            i++;

            if (i < count &&
                tokens[i].type == TOKEN_LEFT_PAREN) {

                i++;

            } else {
                printf("Parser error: expected '('\n");
                return;
            }

            if (i < count &&
                tokens[i].type == TOKEN_STRING) {

                printf("Parser found STRING: %s\n",
                       tokens[i].value);

                i++;

            } else if (i < count &&
                       tokens[i].type == TOKEN_IDENTIFIER) {

                printf("Parser found VARIABLE: %s\n",
                       tokens[i].value);

                i++;

            } else {
                printf("Parser error: expected string or variable\n");
                return;
            }

            if (i < count &&
                tokens[i].type == TOKEN_RIGHT_PAREN) {

                i++;

            } else {
                printf("Parser error: expected ')'\n");
                return;
            }

            if (i < count &&
                tokens[i].type == TOKEN_SEMICOLON) {

                i++;

            } else {
                printf("Parser error: expected ';'\n");
                return;
            }

            printf("Parser: valid print statement!\n\n");

            continue;
        }

        i++;
    }
}