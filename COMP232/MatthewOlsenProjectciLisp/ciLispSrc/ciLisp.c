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
    if (!p)
        return;

    if (p->type == FUNC_TYPE)
    {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
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
                    // TODO
                default:
                    printf("WAT");
    }

    return NAN;
}

AST_NODE *setSymbolTabe(SYMBOL_TABLE_NODE *symbol_table_node, AST_NODE *s_expr)
{
    // if s-expr is Null, return NULL (there is not parent node)
    // set s_expr's sybmbolTalbe to one input
    // go through SymbolTable, assigning each symbol's value's parent to the input s_expr
    // return the input s-expr
}
//TODO
AST_NODE *symbol (char *name)
{
    // allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
        //check if out of memory I guess
    // set the AST_NODE*'s type(symbol)
    // set the AST_NODE*'s symbolTable and parent to NULL
    // set the AST_NODE*'s name (in the SYBMOL_AST_NODE portion of
        //malloc and strcpy
    // return the
}
// TODO
SYMBOL_TABLE_NODE createSymbol(char *name, AST_NODE *value)
{
    // if value is NULL, return NULL (maybe print a warning? symbol with no value?)
    // allocate memory for a SYMBOL_TABLE_NODE
        //out of memory?
    // set the SYMBOL_TABLE_NODE*'s ident string to input name
        //malloc and strcpy...
    // set the SYMBOL_TABLE_NODE'sval to the input value
    // set the SYMBOL_TABLE_NODE*'s next pointer to NULL
    // return the SYMBOL_TABLE_NODE*
}

//TODO
SYMBOL_TABLE_NODE addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol)
{
    // if newSymbol is NULL, return the symbolTable
    //call findSymbol with SymbolTable and newSymbol
        //if result is NULL (i.e. the symbol isn't in the list:
            //set newSymbol's next printer to symbolTable
            // return newSybmol (its now the head )
        // otherwise
            // overwrite the val field of the returned SYJBOL_TABLE NODE with the val from newSymbo
                // overwrit edata in retunred SYMBOL_TABLE_NODE's val AST )NODE with data from
                    // newSymbol's ASTN_NODE
                //free newSymbol
            //retunr the AST_NODE*

}

//TODO
SYMBOL_TABLE_NODE findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol)
{
    // if symbol is NULL, return NULL
    // go through symbolTable (it's a linked list)
        // if a node in symbolTable has the same ident value as symbol, return that node
    //return NULL
}

// TODO
SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node)
{
    // set "parent" to node
    // while parent is not NULL
        // set "symbol" to parent's symbolTable
        // while symbol is not NULL
            // if symbol's ident is the same as input name, return symbol
        // set parent to parent -> parent
        // probably do the above with the loops though; few lines? who cares I guess
    // return NULL
}
