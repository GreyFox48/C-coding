/**
 * @file ciLisp.c
 * @author Matthew Olsen
 * @date 15 May 2019
 * @brief Impliments a basic verision of Lisp, called CiLisp.
 *
 * CiLisp can add, take the absolute value, take the exponent, square root, add, subtract,
 * multiply, divide, take the remainder, take the log, power, max or min of two values, the
 * cube root, deduce the hypotenuse of a given two sides of a right triangle, read a variable,
 * make a random real number, print, and use conditions such as equality, smaller than, and greater
 * than.  Only add, multiply, and print can take a variable amount of values.  Can handle integers
 * and reals.  Can also handle strings.  Strings promote other values to strings, and can
 * be added and printed.
 *
 * @bugs none
 */

#include "ciLisp.h"

#define UNDEFINED_SYMBOL 2000 /* symbol was not defined */
#define UNDEFINED_LAMBDA 2001 /* lambda function was either not defined or variable of wrong type */
#define NULL_EVAL 2002 /* eval function received a NULL parameter */

#define RAND_RANGE 1000 /* range of "rand" function */

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
}

char *func[] = {"neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min",
                "exp2", "cbrt", "hypot", "read", "rand", "print", "equal", "smaller", "larger", ""};
char *type[] = {"no_type", "integer", "real", "string"};

/**
 * Returns a enumerated type based on the given string value.  Unknown function names are
 * assumed to be custom functions.
 * @param funcName the string name of the function
 * @return associated enumerated value for funcName
 */
OPER_TYPE resolveFunc(char *funcName) {
    int i = 0;
    while (func[i][0] != '\0') {
        if (strcmp(func[i], funcName) == 0)
            return i;

        i++;
    }
    return CUSTOM_FUNC;
}

/**
 * Returns a enumerated type based on the given string value.  Unknown types names are
 * assumed to be NO_TYPE, which is an error type.
 * @param typeName the string name of the type
 * @return associated enumerated value for typeName
 */
DATA_TYPE resolveType(char *typeName) {
    int i = 0;
    while (type[i][0] != '\0') {
        if (strcmp(type[i], typeName) == 0)
            return i;

        i++;
    }
    return NO_TYPE;
}

/**
 * Creates an ast_node for a real value.
 * @param value the value of the real ast_node
 * @return an ast_node whose return_type is the same as value
 */
AST_NODE *real_number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value.type = REAL_TYPE;
    p->data.number.value.value.real = value;
    p->parent = NULL;


    return p;
}

/**
 * Creates an ast_node for a integer value.
 * @param value the value of the real ast_node
 * @return an ast_node whose return_type is the same as value
 */
AST_NODE *integer_number(long value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->symbolTable = NULL;
    p->data.number.value.type = INTEGER_TYPE;
    p->data.number.value.value.integer = value;
    p->parent = NULL;
    p->next = NULL;


    return p;
}

/**
 * Creates an ast_node for a string value.
 * @param value the value of the real ast_node
 * @return an ast_node whose return_type is the same as value.  Note that
 * strings are considered NUM types, due to time constraints.
 */
AST_NODE *string(char *s) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE; //REFACTOR THIS
    p->symbolTable = NULL;
    p->data.number.value.type = STRING_TYPE;
    p->data.number.value.value.string = malloc((strlen(s) + 1) * sizeof(char));
    strncpy(p->data.number.value.value.string, s, strlen(s) + 1);
    p->parent = NULL;
    p->next = NULL;


    return p;
}

/**
 * Creates a function ast_node, with a given name and parameter list.
 * @param funcName the name of the function
 * @param s_list the parameter list of the function
 * @return a function ast node with funcName as its name and s_list as its parameters.
 */
AST_NODE *function(char *funcName, AST_NODE *s_list) {
    AST_NODE *p = NULL;
    AST_NODE *child = NULL;
    size_t nodeSize = 0;

    nodeSize = sizeof(AST_NODE);
    p = malloc((nodeSize));
    if (p == NULL) {
        yyerror("out of memory");
    }

    p->type = FUNC_TYPE;
    p->parent = NULL;
    p->symbolTable = NULL;
    p->next = NULL;
    p->data.function.name = funcName;
    p->data.function.opNum = 0;

    p->data.function.opList = s_list;

    for (child = s_list; child != NULL; child = child->next) {
        child->parent = p;
        p->data.function.opNum++;
    }


    return p;
}

/**
 * Frees the associated memory of any given ast_node along with its children recursively.
 * Will free associated symbol_nodes as well.
 * @param p the ast_node to free
 */
void freeAstNode(AST_NODE *p) {
    if (!p)
        return;

    if (p->symbolTable != NULL) freeSymbolNode(p->symbolTable);
    if (p->next != NULL) freeAstNode(p->next);

    if (p->type == FUNC_TYPE) {
        free(p->data.function.name);
        if (p->data.function.opList != NULL) freeAstNode(p->data.function.opList);
    } else if (p->type == COND_TYPE) {
        freeAstNode(p->data.condition.cond);
        freeAstNode(p->data.condition.zero);
        freeAstNode(p->data.condition.nonzero);
    } else if (p->type == SYMB_TYPE) {
        free(p->data.symbol.name);
    } else if (p->type == NUM_TYPE && p->data.number.value.type == STRING_TYPE) {
        free(p->data.number.value.value.string);
    }

    free(p);

}

/**
 * Frees a given symbol_table_node, along with the rest of its chain.  If the
 * symbol contains a stack, frees that too.
 * @param p the symbol_table_node to free
 */
void freeSymbolNode(SYMBOL_TABLE_NODE *p) {

    if (p->next != NULL) freeSymbolNode(p->next);
    if (p->stack != NULL) freeStack(p->stack);

    free(p->ident);
    freeAstNode(p->val);
    free(p);

}

/**
 * Free's the given stack, along with other stack_nodes connected to it.
 * @param stack the stack node to free
 */
void freeStack(STACK_NODE *stack) {
    STACK_NODE *current = stack;
    STACK_NODE *next = current->next;

    for (; next != NULL; current = next, next = next->next) free(current);
}


/**
 * Evaluates the given ast_node, and will resolve the values of children and symbols as needed
 * in order to do so.  The main driver of the program.  If there are too many operands for a
 * given function, it will only evaluate using the first needed operands.  Otherwise, a type
 * of NO_TYPE is given, and its value is set to zero.  A mixture of reals and integers
 * typecasts the result to real, and anything with a string is typecasted to a string.
 * @param p the ast_node to evaluate.
 * @return a return_type containing p's resolved value
 */
RETURN_TYPE eval(AST_NODE *p) {
    SYMBOL_TABLE_NODE *stn = NULL;
    RETURN_TYPE result, op1, op2;
    result.type = NO_TYPE;
    result.value.integer = 0;

    /* Null p's are considered fatal for this implimentation. */
    if (!p) {
        printf("Error:  Eval function received a null value.\n"
               "file %s if function %s at line %d", __FILE__, __FUNCTION__, __LINE__);
        exit(NULL_EVAL);
    }

    /* A huge switch statement.  Its huge to reduce processing power to switch to functions
     * I otherwise realize that most of its functionality could be broken into other
     * functions to make more readable.
     */
    switch (p->type) {
        case NUM_TYPE:
            return p->data.number.value;
        case FUNC_TYPE:
            switch (resolveFunc(p->data.function.name)) {
                case NEG_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"neg\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"neg\"\n");
                    }
                    /* if only one operand, easy to access it */
                    op1 = eval(p->data.function.opList);
                    result.type = op1.type;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.integer = -op1.value.integer;
                    } else {
                        result.value.real = -op1.value.real;
                    }
                    break;
                case ABS_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"abs\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"abs\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = op1.type;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.integer = labs(op1.value.integer);
                    } else {
                        result.value.real = fabs(op1.value.real);
                    }
                    break;
                case EXP_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"exp\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"exp\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = exp(op1.value.integer);
                    } else {
                        result.value.real = exp(op1.value.real);
                    }
                    break;
                case SQRT_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"sqrt\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"sqrt\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = sqrt(op1.value.integer);
                    } else {
                        result.value.real = sqrt(op1.value.real);
                    }
                    break;
                case ADD_OPER: /* only this function can manipulate strings */
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"add\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    }

                    result = addFunc(p);
                    break;
                case SUB_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"sub\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"sub\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.type = INTEGER_TYPE;
                        result.value.integer = op1.value.integer - op2.value.integer;
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer - op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real - (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real - op2.value.real;
                    }
                    break;
                case MULT_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"mult\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    }

                    result = multFunc(p);
                    break;
                case DIV_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"div\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"div\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        if (0 == op1.value.integer % op2.value.integer) {
                            result.type = INTEGER_TYPE;
                            result.value.integer = op1.value.integer / op2.value.integer;
                            break;
                        }
                        result.type = REAL_TYPE;
                        result.value.real = ((double) op1.value.integer) / ((double) op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.type = REAL_TYPE;
                        result.value.real = (double) op1.value.integer / op2.value.real;
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real / (double) op2.value.integer;
                    } else {
                        result.type = REAL_TYPE;
                        result.value.real = op1.value.real / op2.value.real;
                    }
                    break;
                case REMAINDER_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"remainder\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"remainder\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = remainder(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.real = remainder(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = remainder(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = remainder(op1.value.real, op2.value.real);
                    }
                    break;
                case LOG_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"log\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"log\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = log(op1.value.integer);
                    } else {
                        result.value.real = log(op1.value.real);
                    }
                    break;
                case POW_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"pow\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"pow\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = pow(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.real = pow(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = pow(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = pow(op1.value.real, op2.value.real);
                    }
                    break;
                case MAX_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"max\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"max\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = fmax(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.real = fmax(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = fmax(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = fmax(op1.value.real, op2.value.real);
                    }
                    break;
                case MIN_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"min\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"min\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = fmin(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.real = fmin(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = fmin(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = fmin(op1.value.real, op2.value.real);
                    }
                    break;
                case EXP2_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"exp2\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"exp2\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = exp2(op1.value.integer);
                    } else {
                        result.value.real = exp2(op1.value.real);
                    }
                    break;
                case CBRT_OPER:
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"cbrt\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"cbrt\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = cbrt(op1.value.integer);
                    } else {
                        result.value.real = cbrt(op1.value.real);
                    }
                    break;
                case HYPOT_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"hypot\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"hypot\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = hypot(op1.value.integer, op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.real = hypot(op1.value.integer, op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.real = hypot(op1.value.real, op2.value.integer);
                    } else {
                        result.value.real = hypot(op1.value.real, op2.value.real);
                    }
                    break;
                case PRINT_OPER:
                    printFunc(p);
                    break;
                case READ_OPER:
                    if (p->data.function.opNum != 0) {
                        printf("function \"read\" does not take parameters.\n");
                    }
                    char input[255];
                    char buffer[255];
                    printf("%s := ", p->parent->data.symbol.name);
                    scanf(" %[^\n]", input);
                    if (sscanf(input, "\"%s\"", buffer) != EOF) {
                        result.type = STRING_TYPE;
                        result.value.string = malloc(sizeof(char) * (strlen(buffer) + 1));
                        strncpy(result.value.string, buffer, sizeof(char) * (strlen(buffer) + 1));
                    } else if (strchr(input, '.')) {
                        /*found a dot */
                        result.type = REAL_TYPE;
                        result.value.real = strtod(input, NULL);
                    } else {
                        /* no dot will be integer */
                        char **temp = NULL;
                        result.type = INTEGER_TYPE;
                        result.value.integer = strtol(input, temp, 10);
                    }
                    break;
                case RAND_OPER:
                    if (p->data.function.opNum != 0) {
                        printf("function \"rand\" does not take parameters.\n");
                    }
                    result.type = REAL_TYPE;
                    result.value.real = (double) rand() / (double) (RAND_MAX / RAND_RANGE);
                    break;
                case EQUAL_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"equal\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"equal\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);

                    result.type = INTEGER_TYPE;

                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.integer == op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.integer = (((double) op1.value.integer) == op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.real == ((double) op2.value.integer));
                    } else {
                        result.value.integer = (op1.value.real == op2.value.real);
                    }
                    break;
                case SMALLER_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"smaller\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"smaller\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);

                    result.type = INTEGER_TYPE;

                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.integer < op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.integer = (((double) op1.value.integer) < op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.real < ((double) op2.value.integer));
                    } else {
                        result.value.integer = (op1.value.real < op2.value.real);
                    }
                    break;
                case LARGER_OPER:
                    if (p->data.function.opNum < 2) {
                        printf("Warning:  Too few operators for function \"larger\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 2) {
                        printf("Warning:  Too many operators for function \"larger\"\n");
                    }
                    op1 = eval(p->data.function.opList);
                    op2 = eval(p->data.function.opList->next);

                    result.type = INTEGER_TYPE;

                    if (op1.type == INTEGER_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.integer > op2.value.integer);
                    } else if (op1.type == INTEGER_TYPE && op2.type == REAL_TYPE) {
                        result.value.integer = (((double) op1.value.integer) > op2.value.real);
                    } else if (op1.type == REAL_TYPE && op2.type == INTEGER_TYPE) {
                        result.value.integer = (op1.value.real > ((double) op2.value.integer));
                    } else {
                        result.value.integer = (op1.value.real > op2.value.real);
                    }
                    break;
                case CUSTOM_FUNC:
                    stn = resolveSymbol(p->data.symbol.name, p);

                    if (stn->type != LAMBDA_TYPE) {
                        printf("Error:  Custom function did not resolve to a lambda symbol"
                               " in file %s in function %s at line %d.\n  Exiting.\n", __FILE__, __FUNCTION__,
                               __LINE__);
                        exit(UNDEFINED_LAMBDA);
                    }

                    /* pushes the Lambda function parameter's values onto stack */
                    AST_NODE *node = p->data.function.opList;
                    SYMBOL_TABLE_NODE *param = stn->val->symbolTable;
                    STACK_NODE *stack = NULL;
                    for (; node != NULL; node = node->next, param = param->next) {
                        stack = malloc(sizeof(STACK_NODE));
                        stack->val = eval(node);
                        stack->next = param->stack;
                        param->stack = stack;
                    }

                    /* evaluate symbol's val to evaluate the custom function under the specified definition */
                    result = eval(stn->val);

                    /* now enforce typing. */
                    if (stn->data_type == INTEGER_TYPE && result.type == REAL_TYPE) {
                        /* no type warning as assuming user knows integer functions will always
                         * be less accurate.
                         */
                        result.value.integer = result.value.real;
                        result.type = INTEGER_TYPE;
                    } else if (stn->data_type == STRING_TYPE && result.type == REAL_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%lf", result.value.real);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                        result.type = STRING_TYPE;
                    } else if (stn->data_type == STRING_TYPE && result.type == INTEGER_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%ld", result.value.integer);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                        result.type = STRING_TYPE;
                    }

                    break;
                default:
                    result.type = NO_TYPE;
            }
            return result;
        case SYMB_TYPE:
            stn = resolveSymbol(p->data.symbol.name, p);
            if (stn != NULL) {
                if (stn->type == VARIABLE_TYPE) {
                    /* actual result */
                    op1 = eval(stn->val);
                    /* copy over casted result, below ifs will assign as necessary to cast */
                    result.type = stn->data_type;
                    if (op1.type == INTEGER_TYPE && result.type == INTEGER_TYPE) {
                        result.value.integer = op1.value.integer;
                    } else if (op1.type == INTEGER_TYPE && result.type == REAL_TYPE) {
                        result.value.real = op1.value.integer;
                    } else if (op1.type == REAL_TYPE && result.type == INTEGER_TYPE) {
                        printf("Warning, symbol %s has a loss of precision from integer cast.\n", stn->ident);
                        result.value.integer = op1.value.real;
                    } else if (op1.type == INTEGER_TYPE && result.type == STRING_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%ld", op1.value.integer);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                    } else if (op1.type == REAL_TYPE && result.type == STRING_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%lf", op1.value.real);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                    } else if (op1.type == STRING_TYPE && result.type == REAL_TYPE) {
                        result.type = STRING_TYPE;
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else if (op1.type == STRING_TYPE && result.type == INTEGER_TYPE) {
                        result.type = STRING_TYPE;
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else if (op1.type == STRING_TYPE && result.type == STRING_TYPE) {
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else {
                        result.value.real = op1.value.real;
                    }
                } else if (stn->type == ARG_TYPE) {
                    /* retrieve and pop from stack */
                    STACK_NODE *stack = stn->stack;
                    op1 = stack->val;
                    stn->stack = stack->next;
                    free(stack);

                    result.type = stn->data_type;
                    /* enforce casted type to result */
                    if (op1.type == INTEGER_TYPE && result.type == INTEGER_TYPE) {
                        result.value.integer = op1.value.integer;
                    } else if (op1.type == INTEGER_TYPE && result.type == REAL_TYPE) {
                        result.value.real = op1.value.integer;
                    } else if (op1.type == REAL_TYPE && result.type == INTEGER_TYPE) {
                        printf("Warning, symbol %s has a loss of precision form integer cast.\n", stn->ident);
                        result.value.integer = op1.value.real;
                    } else if (op1.type == INTEGER_TYPE && result.type == STRING_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%ld", op1.value.integer);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                    } else if (op1.type == REAL_TYPE && result.type == STRING_TYPE) {
                        char char_array[256];
                        sprintf(char_array, "%lf", op1.value.real);
                        result.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
                        strncpy(result.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
                    } else if (op1.type == STRING_TYPE && result.type == REAL_TYPE) {
                        result.type = STRING_TYPE;
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else if (op1.type == STRING_TYPE && result.type == INTEGER_TYPE) {
                        result.type = STRING_TYPE;
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else if (op1.type == STRING_TYPE && result.type == STRING_TYPE) {
                        result.value.string = malloc(strlen(op1.value.string) * sizeof(char) + 1);
                        strncpy(result.value.string, op1.value.string, strlen(op1.value.string) + 1);
                    } else {
                        result.value.real = op1.value.real;
                    }
                }
            } else {
                char error[256];
                sprintf(error, "Symbol \"%s\" does not exist.\n", p->data.symbol.name);
                yyerror(error);
                exit(UNDEFINED_SYMBOL);
            }
            return result;
        case COND_TYPE:
            /* evaluate and then determine success or failure */
            result = eval(p->data.condition.cond);
            /* on success */
            if (result.value.integer != 0) {
                result = eval(p->data.condition.nonzero);
            } else /* on failure */ {
                result = eval(p->data.condition.zero);
            }

            return result;

        default:
            printf("WAT");
    }

    result.type = NO_TYPE;
    return result;

}

/**
 * Sets the given SYMBOL_TABLE_NODE node/chain's parent to the given AST_NODE
 * @parem symbol_table_node the symbol_table_nodes who's parent(s) will be set
 * @parem s_expr the s_expr that is associated with the scope of symbol_table_node
 * @return the s_expr given
 */
AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbol_table_node, AST_NODE *s_expr) {
    SYMBOL_TABLE_NODE *node = symbol_table_node;
    /* if s-expr is Null, return NULL (there is not parent node) */
    if (NULL == s_expr) {
        return NULL;
    }

    s_expr->symbolTable = symbol_table_node;
    /* go through SymbolTable, assigning each symbol's value's parent to the input s_expr */
    for (; NULL != node; node = node->next) {
        node->val->parent = s_expr;
    }

    return s_expr;
}

/**
 * Creates a symbol ast_node, used to reference the value of the ast node.
 * This reference will then later be used to find the symbol that is storing the value.
 * @parem name the name of the symbol encountered to later be substitued
 * @return the created AST_NODE with the name of the name given
 */
AST_NODE *symbol(char *name) {
    AST_NODE *node = malloc(sizeof(AST_NODE));
    if (NULL == node) {
        yyerror("Out of memory.");
        return NULL;
    }

    node->type = SYMB_TYPE;
    node->symbolTable = NULL;
    node->parent = NULL;
    node->data.symbol.name = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->data.symbol.name) {
        yyerror("Out of memory.");
    }
    strncpy(node->data.symbol.name, name, sizeof(name) + 1);

    free(name);
    return node;
}

/**
 * Creates a symbol table node that stores both its identifier and its AST_NODE that contains
 * its associated value.  The symbol can be casted to a certain type. If the given value
 * is a fucntion of type read, it will prompt for a value. Also frees the given name.
 * @parem name the name of the identifier.  This will be freed!
 * @parem value the pointer to the AST_NODE is the identifier's value
 * @parem type the casted type of the symbol.
 * @return the SYMBOL_TABLE_NODE with the associated name and value, of the given type
 */
SYMBOL_TABLE_NODE *createSymbol(char *type, char *name, AST_NODE *value) {
    SYMBOL_TABLE_NODE *node = NULL;
    if (!value) {
        printf("Symbol %s with no value.\n", name);
        return NULL;
    }
    node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if (NULL == node) {
        yyerror("Out of memory.");
        return NULL;
    }
    node->next = NULL;
    node->stack = NULL;
    node->data_type = REAL_TYPE;
    node->type = VARIABLE_TYPE;

    node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->ident) {
        yyerror("Out of memory.");
    }

    strncpy(node->ident, name, sizeof(name) + 1);
    node->val = value;

    /* resolve read functions now */
    if (value->type == FUNC_TYPE) {
        if (resolveFunc(value->data.function.name) == READ_OPER) {
            if (value->data.function.opNum != 0) {
                printf("function \"read\" does not take parameters.\n");
            }
            char input[255];
            printf("%s := ", name);
            scanf(" %[^\n]", input);
            if (strchr(input, '.')) {
                value->data.number.value.type = REAL_TYPE;
                value->type = NUM_TYPE;
                value->data.number.value.value.real = strtod(input, NULL);

            } else {
                char **temp = NULL;
                value->type = NUM_TYPE;
                value->data.number.value.type = INTEGER_TYPE;
                value->data.number.value.value.integer = strtol(input, temp, 10);
                if (type == NULL) {
                    /* only here do we dynamically figure it out, else defaults to real */
                    node->data_type = INTEGER_TYPE;
                }
            }
        }
    }


    /* needed to prevent resolveType maybe reading a NULL value */
    if ((type != NULL) && (resolveType(type) == INTEGER_TYPE)) {
        node->data_type = INTEGER_TYPE;
    } else if ((type != NULL) && (resolveType(type) == STRING_TYPE)) {
        node->data_type = STRING_TYPE;
    }

    node->next = NULL;
    free(name);

    return node;
}

/**
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

/**
 * Used to check if a variable has already be overwritten in the local scope of symbol tables.
 * ( the same chain of SYMBOL_TABLE_NODES ).
 * @parem symbolTable, the head of the SYMBOL_TABLE_NODE for the chain for the local let statement
 * @parem symbol, the symbol to look for in the chain
 * @return NULL if symbol is not found, the matching SYMBOL_TABLE_NODE is found
 */
SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol) {
    SYMBOL_TABLE_NODE *node = symbolTable;
    if (!symbol) {
        return NULL;
    }
    for (; node != NULL; node = node->next) {
        if (!strcmp(node->ident, symbol->ident)) {
            return node;
        }
    }


    return NULL;
}

/**
 * Looks to find the value of the symbol associated with *name.  If it cannot
 * find it in the current scope, climbs until it reaches the top of the parse
 * tree.
 * @parem char *name name of the symbol to loo for
 * @parem AST_NODE node the node to start from
 * @return the SYMBOL_TABLE_NODE that contains the identifier that matches with name,
 *          otherwise NULL if nothing was found.
 */
SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node) {
    AST_NODE *parent = node;
    SYMBOL_TABLE_NODE *symbol = NULL;
    for (; parent != NULL; parent = parent->parent) {
        symbol = parent->symbolTable;
        for (; symbol != NULL; symbol = symbol->next) {
            if (!strcmp(symbol->ident, name))
                return symbol;
        }
    }
    return NULL;
}

/**
 * Adds the given new operator to an existing operator list, with the new operator at the
 * front of the chain.  If opTable is new, will simply return newOp.
 * @param newOp the new operator to be added to the front of the chain
 * @param opTable the existing opTable. Can be Null
 * @return the new OpTable with NewOp as the head of the chain.
 */
AST_NODE *addOpToList(AST_NODE *newOp, AST_NODE *opTable) {
    if (!newOp) {
        return opTable;
    }

    newOp->next = opTable;
    return newOp;

}

/**
 * Implements the functionality of addition.  Requires at least two operators.
 * Autocasts the results to real if adding integers and reals, and will
 * typecast to string if anything is a string.
 * @param p the addition AST_NODE to evaluate.
 * @return result of the addition.
 */
RETURN_TYPE addFunc(AST_NODE *p) {
    RETURN_TYPE answer, temp;
    AST_NODE *node = NULL;
    char char_array[255];

    if (p->data.function.opList != NULL) {
        answer = eval(p->data.function.opList);
    }

    /* start at the second operand */
    for (node = p->data.function.opList->next; node != NULL; node = node->next) {
        temp = eval(node);
        if (temp.type == INTEGER_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.integer += temp.value.integer;
        } else if (temp.type == REAL_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.real = (double) answer.value.integer;
            answer.type = REAL_TYPE;

            answer.value.real += temp.value.real;
        } else if (temp.type == REAL_TYPE && answer.type == REAL_TYPE) {
            answer.value.real += temp.value.real;
        } else if (temp.type == INTEGER_TYPE && answer.type == REAL_TYPE) {
            answer.value.real += temp.value.integer;
            /* promote existing addition to string */
        } else if (temp.type == STRING_TYPE && answer.type == REAL_TYPE) {
            answer.type = STRING_TYPE;
            sprintf(char_array, "%lf%s", answer.value.real, temp.value.string);
            answer.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
            strncpy(answer.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
        } else if (temp.type == STRING_TYPE && answer.type == INTEGER_TYPE) {
            answer.type = STRING_TYPE;
            sprintf(char_array, "%ld%s", answer.value.integer, temp.value.string);
            answer.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
            strncpy(answer.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
            /* promote concatenation to string */
        } else if (temp.type == REAL_TYPE && answer.type == STRING_TYPE) {
            sprintf(char_array, "%s%lf", answer.value.string, temp.value.real);
            free(answer.value.string);
            answer.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
            strncpy(answer.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
        } else if (temp.type == INTEGER_TYPE && answer.type == STRING_TYPE) {
            sprintf(char_array, "%s%ld", answer.value.string, temp.value.integer);
            free(answer.value.string);
            answer.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
            strncpy(answer.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
            /* concat strings */
        } else if (temp.type == STRING_TYPE && answer.type == STRING_TYPE) {
            sprintf(char_array, "%s%s", answer.value.string, temp.value.string);
            free(answer.value.string);
            answer.value.string = malloc(sizeof(char) * (strlen(char_array) + 1));
            strncpy(answer.value.string, char_array, sizeof(char) * (strlen(char_array) + 1));
        } else {
            printf("Error in %s in %s at line %d: Conditional loop failure.\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    return answer;
}

/**
 * Implement the functionality of multiplication.  Requires at least two operators.
 * Autocasts the results to real if multiplying integers and reals,
 * @param p the multiplication ast_node to evaluate.
 * @return the evaluation of the multiplication node.
 */
RETURN_TYPE multFunc(AST_NODE *p) {
    RETURN_TYPE answer, temp;
    AST_NODE *node = NULL;
    answer.type = INTEGER_TYPE;
    answer.value.integer = 1; /* cheating for mult algorithm that follows. */

    for (node = p->data.function.opList; node != NULL; node = node->next) {
        temp = eval(node);
        if (temp.type == INTEGER_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.integer *= temp.value.integer;
        } else if (temp.type == REAL_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.real = (double) answer.value.integer;
            answer.type = REAL_TYPE;
            answer.value.real *= temp.value.real;
        } else if (temp.type == REAL_TYPE && answer.type == REAL_TYPE) {
            answer.value.real *= temp.value.real;
        } else if (temp.type == INTEGER_TYPE && answer.type == REAL_TYPE) {
            answer.value.real *= temp.value.integer;
        } else {
            printf("Error in %s in %s at line %d: Conditional loop failure.\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    return answer;
}

/**
 * Implements the printing functionality.  Can print strings, reals, and integers. Reals
 * are printed to the first 2 digits.
 * @parem p the AST_NODE containing the value to the printed.
 */
void printFunc(AST_NODE *p) {
    RETURN_TYPE temp;
    AST_NODE *node = NULL;

    for (node = p->data.function.opList; node != NULL; node = node->next) {
        temp = eval(node);
        if (temp.type == INTEGER_TYPE) {
            printf("%ld ", temp.value.integer);
        } else if (temp.type == REAL_TYPE) {
            printf("%.2lf ", temp.value.real);
        } else if (temp.type == STRING_TYPE) {
            printf("%s ", temp.value.string);
        }
    }
    puts("");

}

/**
 * Returns a conditional node, based upon the given AST nodes.
 * @param cond, the conditional of the statement
 * @param nonzero, the s_expr to be evaluated if the conditional returns not zero, or true
 * @param nonzero, the s_expr to be evaluated if the conditional returns zero, or false
 * @return the AST_NODE of conditional type, the data populated with the above information
 */
AST_NODE *conditional(AST_NODE *cond, AST_NODE *nonzero, AST_NODE *zero) {
    AST_NODE *node = malloc(sizeof(AST_NODE));
    if (node == NULL) {
        yyerror("Out of memory.");
    }

    node->type = COND_TYPE;
    node->symbolTable = NULL;
    node->parent = NULL;
    node->next = NULL;

    node->data.condition.cond = cond;
    node->data.condition.nonzero = nonzero;
    node->data.condition.zero = zero;

    node->data.condition.cond->parent = node;
    node->data.condition.zero->parent = node;
    node->data.condition.nonzero->parent = node;

    return node;
}

/**
 * Creates a node for argument symbols.  Argument symbols are used to store a stack of a Lambda
 * function's values to be resolved later.
 * @param name the name of the Lamda function's parameter
 * @return A symbol of ARG_TYPE,
 */
SYMBOL_TABLE_NODE *createArg(char *name) {
    SYMBOL_TABLE_NODE *node = NULL;

    node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if (NULL == node) {
        yyerror("Out of memory.");
        return NULL;
    }
    node->next = NULL;
    node->data_type = REAL_TYPE;

    node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->ident) {
        yyerror("Out of memory.");
    }
    strncpy(node->ident, name, sizeof(name) + 1);

    node->val = NULL;
    node->stack = NULL;
    node->next = NULL;
    node->type = ARG_TYPE;

    free(name);

    return node;
}

/**
 * Creates a symbol that represents a Lambda function.  Creates both the SYMBOL_TABLE_NODE
 * and the associated AST_NODE to represent the Lambda function.
 * @param type the typecast of the function.  If null, defaults to real
 * @param name the name of the Lambda function.
 * @param argList the arguments the Lambda function takes
 * @param symbolList the operation(s) of the function
 * @return a symbol to represent the Lambda function.
 */
SYMBOL_TABLE_NODE *createLambda(char *type, char *name, SYMBOL_TABLE_NODE *argList, AST_NODE *symbolList) {
    SYMBOL_TABLE_NODE *s_node = NULL;

    s_node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if (s_node == NULL) {
        yyerror("Out of memory.");
    }

    s_node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == s_node->ident) {
        yyerror("Out of memory.");
    }
    strncpy(s_node->ident, name, sizeof(name) + 1);

    s_node->val = symbolList;
    s_node->stack = NULL;
    s_node->next = NULL;
    s_node->type = LAMBDA_TYPE;
    if ((type == NULL) || (resolveType(type) == REAL_TYPE)) {
        s_node->data_type = REAL_TYPE;
    } else if (resolveType(type) == INTEGER_TYPE) {
        s_node->data_type = INTEGER_TYPE;
    } else if (resolveType(type) == STRING_TYPE) {
        s_node->data_type = STRING_TYPE;
    }

    symbolList->symbolTable = argList;

    free(name);
    free(type);

    return s_node;


}