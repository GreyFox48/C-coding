%option noyywrap
%option nounput
%option noinput

%{
    #include "ciLisp.h"
%}

digit [0-9]
func "neg"|"abs"|"exp"|"sqrt"|"add"|"sub"|"mult"|"div"|"remainder"|"log"|"pow"|"max"|"min"|"print"|"rand"|"read"|"equal"|"smaller"|"larger"
letter [a-zA-Z]
symbol {letter}+
integer_number [+|-]?{digit}+
real_number [+|-]?{digit}+\.{digit}+
type "integer"|"real"
%%

{integer_number} {
    char **p = NULL;
    yylval.dval = strtol(yytext, p, 10);
    fprintf(stderr, "lex: integer_number dval = %lf\n", yylval.dval);
    return INTEGER_NUMBER;
    }

{real_number} {
    yylval.dval = strtod(yytext, NULL);
    fprintf(stderr, "lex: real_number dval = %lf\n", yylval.dval);
    return REAL_NUMBER;
    }

"quit" {
    fprintf(stderr, "lex: quit\n");
    return QUIT;
    }

"let" {
    fprintf(stderr, "lex: let\n");
    return LET;
    }

"cond" {
    fprintf(stderr, "lex: cond\n");
    return COND;
    }

"lambda" {
    fprintf(stderr, "lex: lambda\n");
    return LAMBDA;
    }

{func} {
    yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char) + 1);
    strcpy(yylval.sval, yytext);
    fprintf(stderr, "lex: FUNC sval = %s\n", yylval.sval);
    return FUNC;
    }

{type} {
    yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char) + 1);
    strcpy(yylval.sval, yytext);
    fprintf(stderr, "lex: TYPE sval = %s\n", yylval.sval);
    return TYPE;
    }

{symbol} {
    yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char) + 1);
    strcpy(yylval.sval, yytext);
    fprintf(stderr, "lex: SYMBOL sval = %s\n", yylval.sval);
    return SYMBOL;
    }

"(" {
    fprintf(stderr, "lex: LPAREN\n");
    return LPAREN;
    }

")" {
    fprintf(stderr, "lex: RPAREN\n");
    return RPAREN;
    }

[\n] {
    fprintf(stderr, "lex: EOL\n");
    YY_FLUSH_BUFFER;
    return EOL;
    }

[ \t] {}; /* skip whitespace */

. { // anything else
    printf("ERROR: invalid character: >>%s<<\n", yytext);
    }

%%

/*
 * DO NOT CHANGE THE FOLLOWING CODE CRITICAL FOR REPL!
 */
int main(void) {

    //   freopen("/dev/null", "w", stderr); // except for this line that can be uncommented to throw away debug printouts

    char *s_expr_str = NULL;
    size_t s_expr_str_len = 0;
    YY_BUFFER_STATE buffer;
    while (true) {
        printf("\n> ");
        getline(&s_expr_str, &s_expr_str_len, stdin);
        s_expr_str[s_expr_str_len++] = '\0';
        s_expr_str[s_expr_str_len++] = '\0';
        buffer = yy_scan_buffer(s_expr_str, s_expr_str_len);
        yyparse();
        yy_delete_buffer(buffer);
    }
}
