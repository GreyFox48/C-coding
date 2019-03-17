#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//the lexer coded as a finite state machine

static int store_char(char *word, size_t max_len, int c, size_t *len)
{
        if (!(*len < max_len))
              return 0;

        word[(*len)++] = c;
        return 1;  

}


int get_tok(char *word, size_t max_len)
{
        int c;
        size_t word_len = 0;
        enum {OP, NUMBER, NEG, WORD} state;
        state = OP;
        int decimal = 0;

        while ((c = getchar()) != EOF) {
                switch (state) {
                case OP:
                        switch (c) {
                        case '*':
                                return TOK_MULT;
                        case '/':
                                return TOK_DIV;
                        case '+':
                                return TOK_ADD;
                        case '-':
                                //lookahead 
                                //is the token followed by a digit or something else?
                                state = NEG;
                                continue;
                        case '^':
                                return TOK_EXP;
                        case '\n':
                                return TOK_NL;
                        case ' ':
                        case '\t':
                                continue;
                        default:
                                if (isdigit(c) || c == '.') {
                                        state = NUMBER;
                                        if (c == '.')
                                                decimal = 1; 
                                        //store current character
                                        if (store_char(word, max_len, c, &word_len) == 0)
                                                return TOK_ERR;
                                        continue;

                                }
                                else if (isalpha(c))
                                {
                                        state = WORD;
                                        //store current character
                                        if (store_char(word, max_len, c, &word_len) == 0)
                                                return TOK_ERR;
                                        continue;
                                }
                                else
                                        return TOK_ERR;
                                
                        }

                case NUMBER:
                        if (isdigit(c)) {
                                if (store_char(word, max_len, c, &word_len) == 0) 
                                        return TOK_ERR;
                                continue;
                        }
                        else if (c == '.') {
                                if (!decimal) {
                                        if (store_char(word, max_len, c, &word_len) == 0) 
                                                return TOK_ERR;
                                        decimal = 1; 
                                        continue;
                                }
                                else
                                        return TOK_ERR; //two decimal places in number
                        }
                        else {
                                switch (c) {
                                case '*':
                                case '/':
                                case '+':
                                case '-':
                                case '^':        
                                case ' ':
                                case '\t':
                                case '\n': 
                                        if (store_char(word, max_len, '\0', &word_len) == 0)
                                                return TOK_ERR;
                                        
                                        ungetc(c, stdin);
                                        return TOK_NUM;
                                default:
                                        //wrong input
                                        return TOK_ERR; 
                                }

                                
                        }
                case NEG:
                        if (isdigit(c)) {
                                if (store_char(word, max_len, '-', &word_len) == 0)
                                        return TOK_ERR;
                                state = NUMBER;
                                ungetc(c, stdin);
                                continue;
                        }
                        else {
                                ungetc(c, stdin);
                                return TOK_SUB; 
                        }
                case WORD:
                        switch (c) {
                        case '*':
                        case '/':
                        case '+':
                        case '-':
                        case '^':        
                        case ' ':
                        case '\t':
                        case '\n':
                        case '0': case '1': case '2': case '3': case '4': case '5':
                        case '6': case '7': case '8': case '9': case '.':
                                if (store_char(word, max_len, '\0', &word_len) == 0)
                                        return TOK_ERR;
                                
                                ungetc(c, stdin);
                                if (strncmp(word, "quit", 5) == 0)
                                        return TOK_QUIT;
                                else
                                        return TOK_ERR;
                        default:
                                if (store_char(word, max_len, c, &word_len) == 0) 
                                        return TOK_ERR;
                                continue;
                        }
                }
        }
        if (ferror(stdin)) {
                clearerr(stdin);
                return TOK_ERR;
        }
        return TOK_EOF;
}
