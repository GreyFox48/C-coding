/**
 * @file lex_lip.h
 * @brief Checks for certain tokens in *.lisp files.
 * @details Check lex_lisp.c for implementation
 *
 * @date April 26, 2016
 * @author Matthew Olsen
 * @bugs None.
 * @todo Nothing
 */ 

#ifndef _LEX_LISP_H_
#define _LEX_LISP_H_

#include <sys/types.h> 
#include <stdio.h>

#define TOK_NL                  1       /* Newline Character */
#define TOK_LPAREN              10      /* Left Parenthesis */
#define TOK_RPAREN              11      /* Right Parenthesis */
#define TOK_EOF                 12      /* End of file */
#define TOK_SEMIC               13      /* Semicolon, indicates comments */

int get_lisp_tok(FILE *fp);

#endif