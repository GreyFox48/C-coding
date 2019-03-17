/**
 * @file bal_paren.c
 * @brief Checks for balanced parenthesis.
 * @details Is only compatible with *.lsip files.  Uses a stack to check for
 * balance.
 *
 * @date April 26, 2016
 * @author Matthew Olsen
 * @bugs Will detect () in strings.
 * @todo Nothing
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "lex_lisp.h"

#define LEN 512
#define INVALID_FILE 1000

void match_paren(FILE *fp);

int main(int argc, char *argv[])
{
        FILE *fp = fopen(argv[1], "r");
        
        if (fp == NULL) {
                printf("The program takes the file to check as the first argument.\n\n");
                printf("Program will state if parenthesis are balanced or not,\n"
                        "and will tell line number of unbalanced parenthesis.\n");
                exit(1000);
        }

        match_paren(fp);

        fclose(fp);
        return 0;
}

/**
 * Checks for balanced parenthesis. Will print a message if balanced, or 
 * will otherwise state the line of the unbalanced parenthesis.
 * @param fp the file to be checked.
 */
void match_paren(FILE *fp)
{
        int tok;
        int c;
        int balanced = 1; /* Boolean for success message */
        int ln = 1;
        char *lparen = "(";
        char *temp = NULL;
        int *n = NULL;

        stack stk_paren = new_stack();
        stack stk_ln = new_stack();

        while (1) {
                switch(tok = get_lisp_tok(fp)) {
                case TOK_NL:
                        ln++;
                        break;
                case TOK_LPAREN:
                        temp = malloc((strlen(lparen) + 1) * sizeof(char));
                                assert(temp);
                        strncpy(temp, lparen, strlen(lparen) + 1);
                        push(stk_paren, (void *) temp);

                        n = malloc(sizeof(int));
                                assert(n);
                        *n = ln;
                        push(stk_ln, (void *) n);
                        break;
                case TOK_RPAREN:
                        if (!is_stack_empty(stk_paren) && !is_stack_empty(stk_ln)) {
                                temp = (char *) pop(stk_paren);
                                n = (int *) pop(stk_ln);
                                free(temp);
                                free(n);
                        } else {
                                printf("Unmatched right parenthesis at line %d.\n", ln);
                                balanced = 0;
                        }                        
                        break;
                case TOK_SEMIC:
                        /* ; indicates a comment in list 
                         * and is thus not important, so munch the line */
                        while ((c = fgetc(fp) != '\n')) {
                                c++;
                        }
                        ln++;           
                        break;
                case TOK_EOF:
                        while (!is_stack_empty(stk_paren) && !is_stack_empty(stk_ln)) {
                                temp = (char *) pop(stk_paren);
                                n = (int *) pop(stk_ln);
                                printf("Unmatched left parenthesis at line %d.\n", *n);
                                free(temp);
                                free(n);
                                balanced = 0;
                        }
                        if (balanced == 1) {
                                printf("Success. Parenthesis are balanced.\n");
                        }
                        free_stack(stk_paren);
                        free_stack(stk_ln);
                        return;
                }
        }
}
