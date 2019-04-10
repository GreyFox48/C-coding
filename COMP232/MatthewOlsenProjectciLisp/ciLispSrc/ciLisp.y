%{
    #include "ciLisp.h"
%}

//general rule of thumb... set parents for s_exprs?

%union {
    double dval;
    char *sval;
    struct ast_node *astNode;
    struct symbol_table_node *symbolNode;
}

%token <sval> FUNC SYMBOL
%token <dval> NUMBER
%token LPAREN RPAREN LET EOL QUIT

%type <astNode> s_expr f_expr
%type <symbolNode> let_elem let_section let_list

%%

program:

    s_expr EOL {
        fprintf(stderr, "yacc: program ::= s_expr EOL\n");
        if ($1) {
            printf("%lf", eval($1));
            freeNode($1);
        }
    };

s_expr:
    NUMBER {
        fprintf(stderr, "yacc: s_expr ::= NUMBER\n");
        $$ = number($1);

    }
    | f_expr {
    	fprintf(stderr, "yacc: s_expr ::= f_expr\n");
        $$ = $1;
    }
    | QUIT {
        fprintf(stderr, "yacc: s_expr ::= QUIT\n");
        exit(EXIT_SUCCESS);
    }
    | error {
        fprintf(stderr, "ERROR\nyacc: s_expr ::= error\n");
        yyerror("unexpected token");
        $$ = NULL;
    }
    |
    SYMBOL {
	fprintf(stderr, "yacc: s_expr ::= SYMBOL\n");
    	$$ = symbol($1);

    }
    | LPAREN let_section s_expr RPAREN {
    	fprintf(stderr, "yacc: LPAREN let_section s_expr RPAREN\n");
    	$$ = setSymbolTable($2, $3);
	//setParent($$, $3);  //this breaks things.  wants to set it to node above?

    };

f_expr:
    LPAREN FUNC s_expr RPAREN {
        fprintf(stderr, "yacc: f_expr ::= LPAREN FUNC expr RPAREN\n");
        $$ = function($2, $3, 0);
        setParent($$, $3);
    }
    | LPAREN FUNC s_expr s_expr RPAREN {
        fprintf(stderr, "yacc: f_expr ::= LPAREN FUNC expr expr RPAREN\n");
        $$ = function($2, $3, $4);
	setParent($$, $3);
	setParent($$, $4);

    };

let_section:
	LPAREN let_list RPAREN {
	        fprintf(stderr, "yacc: let_section ::= LPAREN let_list RPAREN\n");
		$$ = $2;
	}
	| {
		$$ = NULL;
	};

let_list:
	let_list let_elem {
		fprintf(stderr, "yacc: let_list ::= let_list let_elem\n");
		$$ = addSymbolToList($1, $2);
	}
	| LET let_elem {
		fprintf(stderr, "yacc: let_list ::= LET let_elem\n");
		$$ = $2;
	};
let_elem:
	LPAREN SYMBOL s_expr RPAREN {
		fprintf(stderr, "yacc: let_elem ::= LPAREN SYMBOL s_expr RPAREN\n");
		$$ = createSymbol($2, $3);
	};
%%

