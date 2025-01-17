#ifndef __flex_t1_h_
#define __flex_t1_h_

#include <stdio.h>

typedef enum {
      IF_TOKEN = 258, // since Bison will start token at that number
      THEN_TOKEN,
      DO_TOKEN,
      WHILE_TOKEN,
      PRINT_TOKEN,
      NUMBER_TOKEN,
      ID_TOKEN,
      LPAREN_TOKEN,
      RPAREN_TOKEN,
      SEMICOLON_TOKEN,
      ADDOP_TOKEN,
      MULTOP_TOKEN,
      ASSIGN_TOKEN,
      WHITESPACE_TOKEN
      // and so on...
   } TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
