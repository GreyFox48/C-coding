/*
 * Name: Matthew Olsen
 * Lab: Lab 4 Lexical Analysis
 * Date: 02/20/18
 */

#include "scanner.h"

int main(int argc, char **argv)
{
    freopen(argv[1], "r", stdin);

    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                         "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};
    printf("\n");
    token = scannerNestedCases();
    while (token->type != END_OF_INPUT_TOKEN)
    {
        if ( token->strVal == NULL)
            printf("{%s}\n", token2str[token->type]);
        else
            printf("{%s, %s}\n", token2str[token->type], token->strVal);
        freeToken(&token);
        fflush(stdout);
        token = scannerNestedCases();
    }
    printf("{%s, %s}\n", token2str[token->type], token->strVal);
    freeToken(&token);
    fflush(stdout);
    printf("\n");
    exit(EXIT_SUCCESS);
}