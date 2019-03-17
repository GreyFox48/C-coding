/* NOTE: % must be in the first column (no indentation) */

%option noyywrap
%option nounput
%option noinput

digit       [0-9]
number      {digit}+(\.{digit}+)?
letter      [a-zA-Z]
id          {letter}({letter}|{digit}|_)*
addop       [+-]
multop      [*%/]
ws          [ \n\t\r]

%{
   #include "flex_t1.h"
%}

%%

"if"        {return IF_TOKEN;}
"then"      {return THEN_TOKEN;}
"do"        {return DO_TOKEN;}
"while"     {return WHILE_TOKEN;}
"print"     {return PRINT_TOKEN;}
{number}    {return NUMBER_TOKEN;}
{id}        {return ID_TOKEN;}
"("         {return LPAREN_TOKEN;}
")"         {return RPAREN_TOKEN;}
";"         {return SEMICOLON_TOKEN;}
{addop}     {return ADDOP_TOKEN;}
{multop}    {return MULTOP_TOKEN;}
"="         {return ASSIGN_TOKEN;}
{ws}        {return WHITESPACE_TOKEN;}



%%

void yyerror(char *s) {/* dummy */}
