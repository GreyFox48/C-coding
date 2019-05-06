#include "ciLisp.h"

#define UNDEFINED_SYMBOL 2000 /* symbol was not defined */
#define RAND_RANGE 1000 /* range of "rand" function */

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

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


    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *s_list) {
    AST_NODE *p = NULL;
    AST_NODE *child = NULL;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = FUNC_TYPE;
    p->parent = NULL;
    p->symbolTable = NULL;
    p->data.function.name = funcName;
    p->data.function.opNum = 0;

    p->data.function.opList = s_list;

    for (child = s_list; child != NULL; child = child->next) {
        child->parent = p;
        p->data.function.opNum++;
    }


    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    SYMBOL_TABLE_NODE *stn = NULL;
    AST_NODE *temp = NULL;
    if (!p)
        return;

    // probably needs debugging
    if (p->type == FUNC_TYPE) {
        free(p->data.function.name);
        for (temp = p->data.function.opList; temp != NULL; temp = temp->next) {
            freeNode(temp);
        }
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
                    if (p->data.function.opNum < 1) {
                        printf("Warning:  Too few operators for function \"neg\"\n");
                        result.type = REAL_TYPE;
                        result.value.real = 0;
                        break;
                    } else if (p->data.function.opNum > 1) {
                        printf("Warning:  Too many operators for function \"neg\"\n");
                    }
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
                    // 5 points for taylor series
                    op1 = eval(p->data.function.opList);
                    result.type = REAL_TYPE;
                    if (op1.type == INTEGER_TYPE) {
                        result.value.real = sqrt(op1.value.integer);
                    } else {
                        result.value.real = sqrt(op1.value.real);
                    }
                    break;
                case ADD_OPER:
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
                    printf("%s := ", p->parent->data.symbol.name);
                    scanf(" %[^\n]", input);
                    if (strchr(input, '.')) {
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

                    if ( stn != LAMBDA_TYPE ) {
                        printf("Error:  Custom function did not resolve to a lambda symbol"
                               " in file %s in function %s at line %d.\n  Exiting.\n", __FILE__, __FUNCTION__, __LINE__);
                    }

                    /* push onto stack */

                    AST_NODE *node = p->data.function.opList;
                    SYMBOL_TABLE_NODE *param = stn->val->symbolTable;
                    STACK_NODE *stack = NULL;
                    for( ; node != NULL; node = node->next, param = param->next ) {
                        stack = malloc(sizeof(STACK_NODE));
                        stack->val = eval(node);
                        stack->next = param->next;
                        param->next = stack;
                    }

                    /* evaluate symbol's val to evaluate the custom function under the specified definition */
                    result = eval(stn->val);

                    break;
                default:
                    result.type = NO_TYPE;
            }
            return result;
        case SYMB_TYPE:
            if (p)
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
                        printf("Warning, symbol %s has a loss of precision form integer cast.\n", stn->ident);
                        result.value.integer = op1.value.real;
                    } else {
                        result.value.real = op1.value.real;
                    }
                } else if (stn->type == ARG_TYPE) {

        // REDO THIS SO FIRST THING OUT OF STACK IS THE FIRST VAR
                    STACK_NODE *prev_stack = stn->stack;
                    STACK_NODE *next_stack = stn->stack->next;

                    /* special case if stack is only one deep */
                    if ( next_stack == NULL ) {
                        op1 = eval(prev_stack->val);
                        free(prev_stack);
                        stn->stack = NULL;
                    }

                    for (; next_stack->next != NULL; prev_stack = next_stack, next_stack = next_stack->next);

                    op1 = eval(next_stack->val);
                    free(next_stack);
                    prev_stack->next == NULL;

                    result.type = stn->data_type;
                    if (op1.type == INTEGER_TYPE && result.type == INTEGER_TYPE) {
                        result.value.integer = op1.value.integer;
                    } else if (op1.type == INTEGER_TYPE && result.type == REAL_TYPE) {
                        result.value.real = op1.value.integer;
                    } else if (op1.type == REAL_TYPE && result.type == INTEGER_TYPE) {
                        printf("Warning, symbol %s has a loss of precision form integer cast.\n", stn->ident);
                        result.value.integer = op1.value.real;
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
            } else /* failure */ {
                result = eval(p->data.condition.zero);
            }

            return result;

        default:
            printf("WAT");
    }

    result.type = NO_TYPE;
    return result;

}

RETURN_TYPE customFunc(AST_NODE p) {

}

/*
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
    // set s_expr's sybmbolTalbe to one input
    s_expr->symbolTable = symbol_table_node;
    /* go through SymbolTable, assigning each symbol's value's parent to the input s_expr */
    for (; NULL != node; node = node->next) {
        node->val->parent = s_expr;
    }





    /* need to create variable stack.  This point *should* be safe. */
    /*
    for(node = s_expr->symbolTable; node != NULL; node = node->next) {
        if (node == LAMBDA_TYPE) {
            searchLambdaStacks(s_expr, s_expr->symbolTable->val->symbolTable, s_expr->symbolTable->ident);
        }
    }
     */



    return s_expr;
}

void searchLambdaStacks(AST_NODE *s_expr, SYMBOL_TABLE_NODE *start, char *funcName)
{
    AST_NODE* node = NULL;

    for(node = s_expr; node != NULL; node = node->next ) {
        if(node->type == FUNC_TYPE) {
            searchLambdaStacks(node->data.function.opList, start, funcName);
        } else if(node->type == COND_TYPE) {
            searchLambdaStacks(node->data.condition.cond, start, funcName);
            searchLambdaStacks(node->data.condition.nonzero, start, funcName);
            searchLambdaStacks(node->data.condition.zero, start, funcName);

        }
        if(!strcmp(funcName, node->data.function.name)) {
            createLamdaStacks(node->data.function.opList, start);
        }
    }
}

/* try to link stack_nodes with their correct AST_nodes */
void createLamdaStacks(AST_NODE *s_expr, SYMBOL_TABLE_NODE *start)
{
    AST_NODE *node = NULL;
    SYMBOL_TABLE_NODE *param = NULL;
    STACK_NODE *stack = NULL;
    for(node = s_expr, param = start; node != NULL; node = node->next, param = param->next ) {
        if (param->stack == NULL) {
            param->stack = malloc(sizeof(STACK_NODE));
            param->stack->next = NULL;
            param->stack->val = node;
            continue;
        }
        for(stack = param->stack; stack->next != NULL; stack = stack->next) {
            stack->next = malloc(sizeof(STACK_NODE));
            stack->next->next = NULL;
            stack->next->val = node;
        }
    }

}

/*use to reference the value of the ast node.  This reference will then later be used to
 *find the symbol that is storing the value.
 * @parem name the name of the symbol encountered to later be subsituted
 * @return the created AST_NODE with the name of the name given
 */
AST_NODE *symbol(char *name) {
    // allocate memory for an AST_NODE storing a SYMBOL_AST_NODE
    AST_NODE *node = malloc(sizeof(AST_NODE));
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
    free(name);
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
    node->next = NULL;
    node->data_type = REAL_TYPE;
    node->type = VARIABLE_TYPE;

    // set the SYMBOL_TABLE_NODE*'s ident string to input name
    //malloc and strcpy...
    node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->ident) {
        //check if out of memory I guess
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


    /* if(type == NULL) {
        node->data_type = REAL_TYPE;

        node->next = NULL;
    } else */ if ((type != NULL) && (resolveType(type) == INTEGER_TYPE)) {
        node->data_type = INTEGER_TYPE;

        node->next = NULL;
    } /*else if (resolveType(type) == REAL_TYPE){
        node->data_type = REAL_TYPE;

        node->next = NULL;
    } */

    free(name);
    return node;
}

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


    return NULL;
}

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


AST_NODE *addOpToList(AST_NODE *newOp, AST_NODE *opTable) {
    // if newSymbol is NULL, return the symbolTable

    if (!newOp) {
        return opTable;
    }

    newOp->next = opTable;
    return newOp;

}

RETURN_TYPE addFunc(AST_NODE *p) {
    RETURN_TYPE answer, temp;
    AST_NODE *node = NULL;
    answer.type = INTEGER_TYPE;
    answer.value.real = 0;
    answer.value.integer = 0;

    for (node = p->data.function.opList; node != NULL; node = node->next) {
        temp = eval(node);
        if (temp.type == INTEGER_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.integer += temp.value.integer;
        } else if (temp.type == REAL_TYPE && answer.type == INTEGER_TYPE) {
            answer.value.real = (double) answer.value.integer;
            answer.type = REAL_TYPE;

            answer.value.real += temp.value.real;
        } else if (temp.type == REAL_TYPE && answer.type == REAL_TYPE) {
            answer.value.real += answer.value.real;
        } else {
            printf("Error in %s in %s at line %d: Conditional loop failure.\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    return answer;


}

RETURN_TYPE multFunc(AST_NODE *p) {
    RETURN_TYPE answer, temp;
    AST_NODE *node = NULL;
    answer.type = INTEGER_TYPE;
    answer.value.real = 1; /* cheating for mult algorithm later. */
    answer.value.integer = 1.0; /* 1.0 safe to be stored as a float */

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
        } else {
            printf("Error in %s in %s at line %d: Conditional loop failure.\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    return answer;
}

void printFunc(AST_NODE *p) {
    RETURN_TYPE temp;
    AST_NODE *node = NULL;

    for (node = p->data.function.opList; node != NULL; node = node->next) {
        temp = eval(node);
        if (temp.type == INTEGER_TYPE) {
            printf("%ld ", temp.value.integer);
        } else if (temp.type == REAL_TYPE) {
            printf("%.2lf ", temp.value.real);
        }
    }
    puts("");

}

/*
 * Returns a conditional node, based upon the AST nodes.
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

SYMBOL_TABLE_NODE *createArg(char *name)
{
    SYMBOL_TABLE_NODE *node = NULL;

    // allocate memory for a SYMBOL_TABLE_NODE
    node = malloc(sizeof(SYMBOL_TABLE_NODE));
    if (NULL == node) {
        //out of memory?
        yyerror("Out of memory.");
        return NULL;
    }
    node->next = NULL;
    node->data_type = REAL_TYPE;


    // set the SYMBOL_TABLE_NODE*'s ident string to input name
    //malloc and strcpy...
    node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == node->ident) {
        //check if out of memory I guess
        yyerror("Out of memory.");
    }
    strncpy(node->ident, name, sizeof(name) + 1);

    node->val = NULL;
    node->stack = NULL;
    node->next = NULL;

}

SYMBOL_TABLE_NODE *createLambda(char *type, char *name, SYMBOL_TABLE_NODE *argList, AST_NODE *symbolList)
{
    SYMBOL_TABLE_NODE *s_node = NULL;
    s_node = malloc(sizeof(SYMBOL_TABLE_NODE));

    if (NULL == s_node) {
        //check if out of memory I guess
        yyerror("Out of memory.");
    }


    s_node->ident = malloc(sizeof(char) * (strlen(name) + 1));
    if (NULL == s_node->ident) {
        //check if out of memory I guess
        yyerror("Out of memory.");
    }
    strncpy(s_node->ident, name, sizeof(name) + 1);

    s_node->val = symbolList;
    s_node->stack = NULL;
    s_node->next = NULL;
    s_node->type = LAMBDA_TYPE;
    if ( (type == NULL) || (resolveType(type) == REAL_TYPE)) {
        s_node->data_type = REAL_TYPE;
    } else {
        s_node->data_type = INTEGER_TYPE;
    }

    symbolList->symbolTable = argList;
}