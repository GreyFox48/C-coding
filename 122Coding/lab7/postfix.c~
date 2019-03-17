/**
 * @file postfix.c
 * @brief Calculates a postfix line.
 * @details Will evaluate +, -, *, /, and ^.
 *
 * @date April 26, 2016
 * @author Matthew Olsen
 * @bugs None
 * @todo Nothing
 */ 

#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <math.h>

#define MAX_NUM 512   //max chars in number, increase as necessary
#define OPERATOR_ERROR 1000
#define NUMBER_ERROR 1001

/**
 * Calculates a postfix expression from stdin.
 * @return TOK_NL at end of line, TOK_ERR on error.
 */
int calc(void)
{
        int token;
        char num[MAX_NUM];
        char c;
        stack stk = new_stack();
        double *n = NULL;
        double *temp = NULL;

        while (1) {
                switch (token = get_tok(num, sizeof(num))) {
                case TOK_NUM:
                        n = malloc(sizeof(double));
                        *n = strtod(num, NULL);
                        push(stk, (void *) n);
                        break;
                case TOK_MULT:
                        if (stack_count(stk) < 2) {
                                /* eat the remaining characters in stdin */
                                while ((c = getchar()) != '\n')
                                        c++;
                                free_stack(stk);
                                return OPERATOR_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                temp = (double *)pop(stk); 
                                *n = *temp * *n;
                                push(stk, (void *) n);
                                free(temp);
                        }
                        break;    
                case TOK_DIV:
                        if (stack_count(stk) < 2) {
                                while ((c = getchar()) != '\n')
                                        c++;
                                free_stack(stk);
                                return OPERATOR_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                temp = (double *)pop(stk); 
                                *n = *temp / *n;
                                push(stk, (void *) n);
                                free(temp);
                        }
                        break;
                case TOK_ADD:
                        if (stack_count(stk) < 2) {
                                while ((c = getchar()) != '\n')
                                        c++;
                                free_stack(stk);
                                return OPERATOR_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                temp = (double *)pop(stk); 
                                *n = *temp + *n;
                                push(stk, (void *) n);
                                free(temp);
                        }
                        break;
                case TOK_SUB:
                        if (stack_count(stk) < 2) {
                                while ((c = getchar()) != '\n')
                                        c++;
                                free_stack(stk);
                                return OPERATOR_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                temp = (double *)pop(stk); 
                                *n = *temp - *n;
                                push(stk, (void *) n);
                                free(temp);
                        }
                        break;
                case TOK_EXP:
                        if (stack_count(stk) < 2) {
                                while ((c = getchar()) != '\n')
                                        c++;
                                free_stack(stk);
                                return OPERATOR_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                temp = (double *)pop(stk); 
                                *n = pow(*temp, *n);
                                push(stk, (void *) n);
                                free(temp);
                        }
                        break;
                case TOK_NL:
                        if (is_stack_empty(stk)) {
                                free_stack(stk);
                                return NUMBER_ERROR;
                        } else {
                                n = (double *)pop(stk);
                                printf("Value: %lf\n", *n);
                        }
                        free(n);
                        free_stack(stk);
                        return TOK_NL;
                case TOK_QUIT:
                        free_stack(stk);
                        exit(EXIT_SUCCESS);
                case TOK_EOF:
                        free_stack(stk);
                        exit(EXIT_SUCCESS);
                case TOK_ERR:
                        printf("TOK_ERR\n");
                        /* eat the remaining characters in stdin */
                        while ((c = getchar()) != '\n')
                                c++;
                        free_stack(stk);
                        return TOK_ERR;         
                }
        }
}


int main(void)
{
        int tok = TOK_NL;
        char *prompt = "postfix> ";

        printf("Welcome to the postfix calculator\n");
        printf("Enter a postfix expression -- all expressions are converted to floating point and evaluated\n");
        printf("Enter CTRL + C to quit or type \"quit\"\n");

        while (1) {
                if (tok == TOK_NL)
                        printf("%s", prompt);
                
                tok = calc();

                //an error occur?
                if (tok == TOK_ERR) {
                       fprintf(stderr, "error in postfix expression\n");
                       tok = TOK_NL; 
                }
                if (tok == OPERATOR_ERROR) {
                        fprintf(stderr, "ERROR: Not enough numbers for amount of operators.\n");
                        tok = TOK_NL;
                }
                if (tok == NUMBER_ERROR) {
                        fprintf(stderr, "ERROR: Not enough operators for amount of numbers.\n");
                        tok = TOK_NL;
                }
        }

        return 0;
}

