/**
 * Matthew Olsen
 * March 27, 2019
 * COMP 232L Lab 8 Introduction to Bison
 */

#include "calc.h"
#include <math.h>

void yyerror(char *s) {
    printf("\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

/*
 * The function to resolve a name of a function; i.e., to translate it to an int equivalent (if possible)
 * that can be used conveniently in the src() function.
 */
int resolveFunc(char *func) {
    // all functions are exactly as they appear in math.h; use man to get details
    char *funcs[] = {"neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min",
                     ""};

    int i = 0;
    while (funcs[i][0] != '\0') {
        if (!strcmp(funcs[i], func))
            return i;

        i++;
    }
    yyerror("invalid function"); // paranoic -- should never happen
    return -1;
}

/*
 * The function to calculate simple math operation.
 *
 * The values of op1 and op2 may be omitted for functions that take one or no parameters.
 */
double calc(char *func, double op1, double op2) {

// TODO: implement the function, so it returns correct values for each set of parameters
    double result;
    switch (resolveFunc(func)) {
        case NEG:
            result = -op1;
            break;
        case ABS:
            result = fabs(op1);
            break;
        case EXP:
            result = exp(op1);
            break;
        case SQRT:
            result = sqrt(op1);
            break;
        case ADD:
            result = op1 + op2;
            break;
        case SUB:
            result = op1 - op2;
            break;
        case MULT:
            result = op1 * op2;
            break;
        case DIV:
            if (op2 == 0) {
                result = NAN;
            } else {
                result = op1 / op2;
            }
            break;
        case REMAINDER:
            result = remainder(op1, op2);
            break;
        case LOG:
            if (op2 != 0) {
                if (op2 == 1) {
                    return NAN; /* result of any log of 1 is 0.  Avoiding div by 0 error */
                }
                result = log(op1) / log(op2);
            } else {
                result = log(op1);
            }
            break;
        case POW:
            result = pow(op1, op2);
            break;
        case MAX:
            result = fmax(op1, op2);
            break;
        case MIN:
            result = fmin(op1, op2);
            break;
        default:
            result = NAN;

    }
    return result;

}  
