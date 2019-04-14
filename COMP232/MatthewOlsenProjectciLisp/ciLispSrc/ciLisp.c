#include "ciLisp.h"

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

//
// find out which function it is
//

char *func[] = {"neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min",
                "exp2", "cbrt", "hypot", "read", "rand", "print", "equal", "smaller", "larger", ""};
char *type[] = {"no_type", "integer", "real", ""};
OPER_TYPE resolveFunc(char *funcName) {
    int i = 0;
    while (func[i][0] != '\0') {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

DATA_TYPE resolveType(char *typeName) {
    int i = 0;
    while (type[i][0] != '\0') {
        if (strcmp(type[i], typeName) == 0)
            return i;

        i++;
    }
    return NO_TYPE;
}

//
// create a node for a number
//
/*
AST_NODE *number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value = value;
    p->parent = NULL;


    return p;
}
*/
AST_NODE *real_number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE) + sizeof(double);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value.type = REAL_TYPE;
    p->data.number.value.value.real = value;
    p->parent = NULL;


    return p;
}

AST_NODE *integer_number(long value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE) + sizeof(long);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value.type = INTEGER_TYPE;
    p->data.number.value.value.integer = value;
    p->parent = NULL;


    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->parent = NULL;
    p->data.function.name = funcName;

    p->data.function.op1 = op1;
    p->data.function.op2 = op2;

    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    SYMBOL_TABLE_NODE *stn = NULL;
    if (!p)
        return;

    if (p->type == FUNC_TYPE) {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
    }

    if (p->type == SYMB_TYPE) {
        free(p->data.symbol.name);
    }

    if (p->symbolTable != NULL) {
        stn = p->symbolTable;
        for (; stn != NULL; stn = stn->next) {
            free(stn->ident);
            freeNode(stn->val);
        }
    }
    free(p);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
RETURN_TYPE eval(AST_NODE *p) {
    SYMBOL_TABLE_NODE *stn = NULL;
    RETURN_TYPE result, op1, op2;
    if (!p) {
        result.type = NO_TYPE;
    }

    switch (p->type) {
        case NUM_TYPE:
            return p->data.number.value;
        case FUNC_TYPE:
            switch (resolveFunc(p->data.function.name)) {
                case NEG_OPER:
                    puts("");
                    op1 = eval(p->data.function.op1);
                    result.type = op1.type;
                    if(op1.type == INTEGER_TYPE ) {
                        result.value.integer = -op1.value.integer;
                    } else {
                        result.value.real = -op1.value.real;
                    }
                    break;
                case ABS_OPER:
                    op1 = eval(p->data.function.op1);
                    result.type = op1.type;
                    if(op1.type == INTEGER_TYPE ) {
                        result.value.integer = labs(op1.value.integer);
                    } else {
                        result.value.real = fabs(op1.value.real);
                    }
                    break;
                case EXP_OPER:
                    op1 = eval(p->data.function.op1);
                    result.type = REAL_TYPE;
                    if(op1.type == INTEGER_TYPE) {
                        result.value.real = exp(op1.value.integer);
                    } else {
                        result.value.real = exp(op1.value.real);
                    }
                    break;
                case SQRT_OPER:
                    // 5 points for taylor series
                    op1 = eval(p->data.function.op1);
                    result.type = REAL_TYPE;
                    if(op1.type == INTEGER_TYPE) {
                        result.value.real = sqrt(op1.value.integer);
                    } else {
                        result.value.real = sqrt(op1.value.real);
                    }
                    break;
                case ADD_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.type = INTEGER_TYPE;
                        result.value.integer = op1.value.integer + op2.value.integer;
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer + op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real + (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real + op2.value.real;
                    }
                    break;
                case SUB_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.type = INTEGER_TYPE;
                        result.value.integer = op1.value.integer - op2.value.integer;
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer - op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real - (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real - op2.value.real;
                    }
                    break;
                case MULT_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.type = INTEGER_TYPE;
                        result.value.integer = op1.value.integer * op2.value.integer;
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer * op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real * (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real * op2.value.real;
                    }
                    break;
                case DIV_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        if ( 0 == op1.value.integer % op2.value.integer ) {
                            result.type = INTEGER_TYPE;
                            result.value.integer = op1.value.integer / op2.value.integer;
                            break;
                        }
                        result.type = REAL_TYPE;
                        result.value.integer = ((double) op1.value.integer) / ((double)op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer / op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real / (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real / op2.value.real;
                    }
                    break;
                case REMAINDER_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.value.real = remainder(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.value.real = remainder(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.value.real = remainder(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = remainder(op1.value.real, op2.value.real);
                    }
                    break;
                case LOG_OPER:
                    op1 = eval(p->data.function.op1);
                    result.type = REAL_TYPE;
                    if(op1.type == INTEGER_TYPE) {
                        result.value.real = log(op1.value.integer);
                    } else {
                        result.value.real = log(op1.value.real);
                    }
                    break;
                case POW_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.value.real = pow(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.value.real = pow(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.value.real = pow(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = pow(op1.value.real, op2.value.real);
                    }
                    break;
                case MAX_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.value.real = fmax(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.value.real = fmax(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.value.real = fmax(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = fmax(op1.value.real, op2.value.real);
                    }
                    break;
                case MIN_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.value.real = fmin(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.value.real = fmin(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.value.real = fmin(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = fmin(op1.value.real, op2.value.real);
                    }
                    break;
                case EXP2_OPER:
                    op1 = eval(p->data.function.op1);
                    result.type = REAL_TYPE;
                    if(op1.type == INTEGER_TYPE) {
                        result.value.real = exp2(op1.value.integer);
                    } else {
                        result.value.real = exp2(op1.value.real);
                    }
                    break;
                case CBRT_OPER:
                    op1 = eval(p->data.function.op1);
                    result.type = REAL_TYPE;
                    if(op1.type == INTEGER_TYPE) {
                        result.value.real = cbrt(op1.value.integer);
                    } else {
                        result.value.real = cbrt(op1.value.real);
                    }
                    break;
                case HYPOT_OPER:
                    op1 = eval(p->data.function.op1);
                    op2 = eval(p->data.function.op2);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE ) {
                        result.value.real = hypot(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE){
                        result.value.real = hypot(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE){
                        result.value.real = hypot(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = hypot(op1.value.real, op2.value.real);
                    }
                    break;
                default:
                    result.type = NO_TYPE;
            }
            return result;
        case SYMB_TYPE:
            stn = resolveSymbol(p->data.symbol.name, p);
            if (stn != NULL) {
                op1 = eval(stn->val);
                result.type = op1.type;
                if(op1.type == INTEGER_TYPE ) {
                    result.value.integer = op1.value.integer;
                } else {
                    result.value.real = op1.value.real;
                }
            } else {
                char error[256];
                sprintf(error, "Symbol \"%s\" does not exist.\n", p->data.symbol.name);
                yyerror(error);
                exit(2000);
            }
            return result;
        default:
            printf("WAT");
    }

    result.type = NO_TYPE;
    return result;

}

/*
 * Sets the given SYMBOL_TABLE_NODE node/chain's parent to the given s_expr
 * @parem symbol_table_node the symbol_table_nodes who's parent(s) will be set
 * @parem s_expr the s_expr that is associated with the scope of symbol_table_node
 * @return the s_expr given
 */
AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbol_table_node, AST_NODE *s_expr) {
    SYMBOL_TABLE_NODE *node = symbol_table_node;
    // if s-expr is Null, return NULL (there is not parent node)
    if (NULL == s_expr) {
        return NULL;
    }
    // set s_expr's sybmbolTalbe to one input
    s_expr->symbolTable = symbol_table_node;
    // go through SymbolTable, assigning each symbol's value's parent to the input s_expr
    for (; NULL != node; node = node->next) {
        node->val->parent = s_expr;
    }
    // return the input s-expr
    return s_expr;
}

//TODO
/*use to reference the value of the ast node.  This reference will then later be used to
 *find the symbol that is storing the value.
 * @parem name the name of the symbol encountered to later be subsituted
 * @return the created AST_NODE with the name of the name given
 */
AST_NODE *symbol(char *name) {
    // allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
    AST_NODE *node = malloc(sizeof(AST_NODE) + sizeof(SYMBOL_AST_NODE));
    if (NULL == node) {
        //check if out of memory I guess
        yyerror("Out of memory.");
        return NULL;
    }

    // set the AST_NODE*'s type(symbol)
    node->type = SYMB_TYPE;
    // set the AST_NODE*'s symbolTable and parent to NULL
    node->symbolTable = NULL;
    node->parent = NULL;
    // set the AST_NODE*'s name (in the SYBMOL_AST_NODE portion of
    node->data.symbol.name = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->data.symbol.name) {
        //check if out of memory I guess
        yyerror("Out of memory.");
    }
    strncpy(node->data.symbol.name, name, sizeof(name) + 1);
    //malloc and strcpy
    // return the ast_node
    return node;
}

/*
 * Creates a symbol table node that stores both its identifier and its AST_NODE that points
 * to the value associated to the identifier
 * @parem name the name of the identifier
 * @parem value the pointer to the AST_NODE that holds the identifier's value
 * @return the SYMBOL_TABLE_NODE with the associated name and value
 */
SYMBOL_TABLE_NODE *createSymbol(char *type, char *name, AST_NODE *value) {
    // if value is NULL, return NULL (maybe print a warning? symbol with no value?)
    SYMBOL_TABLE_NODE *node = NULL;
    if (!value) {
        printf("Symbol %s with no value.\n", name);
        return NULL;
    }
    // allocate memory for a SYMBOL_TABLE_NODE
    node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if (NULL == node) {
        //out of memory?
        yyerror("Out of memory.");
        return NULL;
    }
    // set the SYMBOL_TABLE_NODE*'s ident string to input name
    //malloc and strcpy...
    node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->ident) {
        //check if out of memory I guess
        yyerror("Out of memory.");
    }
    strncpy(node->ident, name, sizeof(name) + 1);
    // set the SYMBOL_TABLE_NODE's val to the input value
    /* node->val = value; */
    node->val = malloc(sizeof(AST_NODE));
    if (!node->val) {
        printf("Symbol %s with no value.\n", name);
        return NULL;
    }

    //node->val = value;
    /* evaluate node now instead of later. */

    if(type == NULL) {
        node->data_type = REAL_TYPE;
        node->val->type = NUM_TYPE;
        node->val->parent = NULL;
        node->val->symbolTable = NULL;
        node->val->data.number.value = eval(value);
        /*
        value->data.number.value = eval(value);
        value->type = NUM_TYPE;
         */
        if(node->val->data.number.value.type == INTEGER_TYPE) {
            node->val->data.number.value.value.real = (double) node->val->data.number.value.value.integer;
        }
        node->val->data.number.value.type = REAL_TYPE;
        // set the SYMBOL_TABLE_NODE*'s next pointer to NULL
        node->next = NULL;
        // return the SYMBOL_TABLE_NODE*
    } else if (resolveType(type) == INTEGER_TYPE){
        node->data_type = INTEGER_TYPE;
        node->val->type = NUM_TYPE;
        node->val->parent = NULL;
        node->val->symbolTable = NULL;
        node->val->data.number.value = eval(value);
        if (node->val->data.number.value.type == REAL_TYPE) {
            printf("WARNING: precision loss in the assignment for variable \"%s\"\n", name);
            node->val->data.number.value.value.integer = node->val->data.number.value.value.real;
        }
        node->val->data.number.value.type = INTEGER_TYPE;
        // set the SYMBOL_TABLE_NODE*'s next pointer to NULL
        node->next = NULL;
        // return the SYMBOL_TABLE_NODE*
    } else if (resolveType(type) == REAL_TYPE){
        node->data_type = REAL_TYPE;
        node->val->type = NUM_TYPE;
        node->val->parent = NULL;
        node->val->symbolTable = NULL;
        node->val->data.number.value = eval(value);
        node->val->data.number.value.type = REAL_TYPE;
        if(node->val->data.number.value.type == INTEGER_TYPE) {
            node->val->data.number.value.value.real = (double) node->val->data.number.value.value.integer;
        }
        // set the SYMBOL_TABLE_NODE*'s next pointer to NULL
        node->next = NULL;
        // return the SYMBOL_TABLE_NODE*
    }


    return node;
}

//TODO
/*
 * Adds newSymbol to symbolTable, which is the local scope of symbol tables
 * ( the same chain of SYMBOL_TABLE_NODES ). If newSymbol has a redunant ident,
 * replaces the old SYMBOL_TABLE_NODE with the value of newSymbol
 * @parem symbolTable the symbol Table to look through
 * @parem newSymbol the symbol to add to symbol table
 * @return the head of the new appended symbol table
 */
SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol) {
    // if newSymbol is NULL, return the symbolTable
    SYMBOL_TABLE_NODE *node = NULL;
    if (!newSymbol) {
        return symbolTable;
    }
    //call findSymbol with SymbolTable and newSymbol
    node = findSymbol(symbolTable, newSymbol);
    if (!node) {
        //if result is NULL (i.e. the symbol isn't in the list:
        //set newSymbol's next printer to symbolTable
        newSymbol->next = symbolTable;
        // return newSybmol (its now the head )
        return newSymbol;
    } else {
        // otherwise
        // overwrite the val field of the returned SYJBOL_TABLE NODE with the val from newSymbo
        node->val = newSymbol->val;
        // overwrite data in returned SYMBOL_TABLE_NODE's val AST_NODE with data from newSymbol's ASTN_NODE
        //free newSymbol
        free(newSymbol);
        //retunr the AST_NODE*
        return symbolTable;
    }

}

/*
 * Used to check if a variable has already be overwritten in the local scope of symbol tables.
 * ( the same chain of SYMBOL_TABLE_NODES ).
 * @parem symbolTable, the head of the SYMBOL_TABLE_NODE for the chain for the local
 *          let statment
 * @parem symbol, the symbol to look for in the chain
 * @return NULL if symbol is not found, the matching SYMBOL_TABLE_NODE is found
 */
SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol) {
    // if symbol is NULL, return NULL
    SYMBOL_TABLE_NODE *node = symbolTable;
    if (!symbol) {
        return NULL;
    }
    // go through symbolTable (it's a linked list)
    for (; node != NULL; node = node->next) {
        // if a node in symbolTable has the same ident value as symbol, return that node
        if (!strcmp(node->ident, symbol->ident)) {
            return node;
        }
    }
    //return NULL
    return NULL;
}

// TODO
/*
 * Looks to find the value of the symbol associated with *name.  If it cannot
 * find it in the current scope, climbs until it reaches the top of the parse
 * tree.
 * @parem char *name name of the symbol to loo for
 * @parem AST_NODE node the node to start from
 * @return the SYMBOL_TABLE_NODE that contains the identifier that matches with name,
 *          otherwise NULL if nothing was found.
 */
SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node) {
    // set "parent" to node
    AST_NODE *parent = node;
    SYMBOL_TABLE_NODE *symbol = NULL;
    // while parent is not NULL
    for (; parent != NULL; parent = parent->parent) {
        // set "symbol" to parent's symbolTable
        symbol = parent->symbolTable;
        // while symbol is not NULL
        for (; symbol != NULL; symbol = symbol->next) {
            // if symbol's ident is the same as input name, return symbol
            if (!strcmp(symbol->ident, name))
                return symbol;
        }
        // set parent to parent -> parent
    }
    // return NULL
    return NULL;
}

//how is parent resolved to previous AST!?
void setParent(AST_NODE *parent, AST_NODE *child) {
    child->parent = parent;
}
