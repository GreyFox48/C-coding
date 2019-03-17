/**
 * @file lex_lisp.c
 * @brief Returns tokens upon finding certain characters.
 * @details Reads individaul characters from stream until 
 * encounters a specified character or EOF.
 *
 * @date April 26, 2016
 * @author Matthew Olsen
 * @bugs Will detect () in strings.
 * @todo Nothing
 */ 

#include "lex_lisp.h"
#include <string.h>

/**
 * Returns tokens upon finding certain characters from stream.
 * @param fp the file to read from
 */
int get_lisp_tok(FILE *fp)
{
        int c;
        while ((c = fgetc(fp)) != EOF) {
                switch (c) {
                case '(':
                        return TOK_LPAREN;
                case ')':
                        return TOK_RPAREN;
                case '\n':
                        return TOK_NL;
                case ';':
                        return TOK_SEMIC;
                default:
                        continue;
                }
        }
        return TOK_EOF;
}