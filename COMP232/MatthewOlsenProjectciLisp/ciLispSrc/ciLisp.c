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

OPER_TYPE resolveFunc(char *funcName)
{
    int i = 0;
    while (func[i][0] != '\0')
    {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

//
// create a node for a number
//
AST_NODE *number(double value)
{
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

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
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
void freeNode(AST_NODE *p)
{
    SYMBOL_TABLE_NODE *stn = NULL;
    if (!p)
        return;


    // debugging
    if (p->parent == NULL) {
        printf("My name is ");
        switch (p->type) {
            case FUNC_TYPE:
                printf("function of type %s.  I have no parent!\n", p->data.function.name);
                break;
            case SYMB_TYPE:
                printf("%s.  I have no parent!\n", p->data.symbol.name);
                break;
            case NUM_TYPE:
                printf("%lf.  I have no parent!\n", p->data.number.value);
                break;
        }
    }

    // debugging
    if (p->parent != NULL) {
        printf("My name is ");
        switch (p->type) {
            case FUNC_TYPE:
                printf("function of type %s.  I have a parent!\n", p->data.function.name);
                break;
            case SYMB_TYPE:
                printf("%s.  I have a parent!\n", p->data.symbol.name);
                break;
            case NUM_TYPE:
                printf("%lf.  I have a parent!\n", p->data.number.value);
                break;
        }
    }


    if (p->type == FUNC_TYPE)
    {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
    }

    if(p->type == SYMB_TYPE ) {
        free(p->data.symbol.name);
    }

    if(p->symbolTable != NULL) {
        stn = p->symbolTable;
        for(; stn != NULL; stn = stn->next) {
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
double eval(AST_NODE *p)
{
    SYMBOL_TABLE_NODE *stn = NULL;
    if (!p)
        return NAN;

// TBD: implement
    switch (p->type) {
        case NUM_TYPE:
            return p->data.number.value;
        case FUNC_TYPE:
            switch (resolveFunc(p->data.function.name)) {
                case NEG_OPER:
                    return -eval(p->data.function.op1);
                case ABS_OPER:
                    return fabs(eval(p->data.function.op1));
                case EXP_OPER:
                    return exp(eval(p->data.function.op1));
                case SQRT_OPER:
                                                                                    // 5 points for taylor series
                    return sqrt(eval(p->data.function.op1));
                case ADD_OPER:
                    return eval(p->data.function.op1) + eval(p->data.function.op2);
                case SUB_OPER:
                    return eval(p->data.function.op1) - eval(p->data.function.op2);
                case MULT_OPER:
                    return eval(p->data.function.op1) * eval(p->data.function.op2);
                case DIV_OPER:
                    return eval(p->data.function.op1) / eval(p->data.function.op2);
                case REMAINDER_OPER:
                    return remainder(eval(p->data.function.op1), eval(p->data.function.op2));
                case LOG_OPER:
                    return log(eval(p->data.function.op1));
                case POW_OPER:
                    return pow(eval(p->data.function.op1), eval(p->data.function.op2));
                case MAX_OPER:
                    return fmax(eval(p->data.function.op1), eval(p->data.function.op2));
                case MIN_OPER:
                    return fmin(eval(p->data.function.op1), eval(p->data.function.op2));
                case EXP2_OPER:
                    return exp2(eval(p->data.function.op1));
                case CBRT_OPER:
                    return cbrt(eval(p->data.function.op1));
                case HYPOT_OPER:
                    return hypot(eval(p->data.function.op1), eval(p->data.function.op2));
                default:
                    return NAN;
            }
                case SYMB_TYPE:
                    stn = resolveSymbol(p->data.symbol.name, p);
                    if (stn != NULL) {
                        return eval(stn->val);
                    } else {
                        return NAN;
                    }
                    //return eval(resolveSymbol(p->data.symbol.name, p)->val);
                default:
                    printf("WAT");
    }

    return NAN;
}

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbol_table_node, AST_NODE *s_expr)
{
    SYMBOL_TABLE_NODE *node = symbol_table_node;
    // if s-expr is Null, return NULL (there is not parent node)
    if(NULL == s_expr) {
        return NULL;
    }
    // set s_expr's sybmbolTalbe to one input
    s_expr->symbolTable = symbol_table_node;
    // go through SymbolTable, assigning each symbol's value's parent to the input s_expr
    for ( ; NULL != node; node = node->next) {
        node->val->parent = s_expr;
    }
    // return the input s-expr
    return s_expr;
}
//TODO
// WHAT IS THIS!?!?!?!?
// why care about symbol's name vs symbol_table_node ident?
AST_NODE *symbol(char *name)
{
    // allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
    AST_NODE *node = malloc(sizeof(AST_NODE) + sizeof(SYMBOL_AST_NODE)) ;
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
// TODO
SYMBOL_TABLE_NODE *createSymbol(char *name, AST_NODE *value)
{
    // if value is NULL, return NULL (maybe print a warning? symbol with no value?)
    SYMBOL_TABLE_NODE *node = NULL;
    if(!value) {
        printf("Symbol %s with no value.\n", name);
        return NULL;
    }
    // allocate memory for a SYMBOL_TABLE_NODE
    node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if(NULL  == node) {
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
    if(!node->val) {
        printf("Symbol %s with no value.\n", name);
        return NULL;
    }
    /* evaluate node now instead of later. */
    node->val->type = NUM_TYPE;
    node->val->parent = NULL;
    node->val->symbolTable = NULL;
    node->val->data.number.value = eval(value);
    // set the SYMBOL_TABLE_NODE*'s next pointer to NULL
    node->next = NULL;
    // return the SYMBOL_TABLE_NODE*
    return node;
}

//TODO
SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol)
{
    // if newSymbol is NULL, return the symbolTable
    SYMBOL_TABLE_NODE *node = NULL;
    if (!newSymbol) {
        return symbolTable;
    }
    //call findSymbol with SymbolTable and newSymbol
    node = findSymbol(symbolTable, newSymbol);
    if(!node) {
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

//TODO
SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol)
{
    // if symbol is NULL, return NULL
    SYMBOL_TABLE_NODE *node = symbolTable;
    if (!symbol) {
        return NULL;
    }
    // go through symbolTable (it's a linked list)
    for ( ; node != NULL; node = node->next) {
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
 * Description of the fucntion
 * @paremeters char *name, AST_NNODE node
 *
 * @return some english explanation of expected returns
 */
SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node)
{
    // set "parent" to node
    AST_NODE *parent = node;
    SYMBOL_TABLE_NODE *symbol = NULL;
    // while parent is not NULL
    for( ;parent != NULL; parent = parent->parent) {
        // set "symbol" to parent's symbolTable
        symbol = parent->symbolTable;
        // while symbol is not NULL
        for(;symbol != NULL; symbol = symbol->next) {
            // if symbol's ident is the same as input name, return symbol
            if(!strcmp(symbol->ident, name))
                return symbol;
        }
        // set parent to parent -> parent
    }
    // return NULL
    return NULL;
}
//how is parent resolved to previous AST!?
void setParent(AST_NODE *parent, AST_NODE *child)
{
    child->parent = parent;
}
