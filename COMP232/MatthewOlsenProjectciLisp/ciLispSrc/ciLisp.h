#ifndef __cilisp_h_
#define __cilisp_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "ciLispParser.h"

int yyparse(void);

int yylex(void);

void yyerror(char *);

typedef enum oper { // must be in sync with funcs in resolveFunc()
    NEG_OPER, // 0
    ABS_OPER, // 1
    EXP_OPER, // 2
    SQRT_OPER, // 3
    ADD_OPER, // 4
    SUB_OPER, // 5
    MULT_OPER, // 6
    DIV_OPER, // 7
    REMAINDER_OPER, // 8
    LOG_OPER, // 9
    POW_OPER, // 10
    MAX_OPER, // 11
    MIN_OPER, // 12
    EXP2_OPER, // 13
    CBRT_OPER, // 14
    HYPOT_OPER, // 15
    READ_OPER,  // 16
    RAND_OPER,  //17
    PRINT_OPER, //18
    EQUAL_OPER, //19
    SMALLER_OPER, //20
    LARGER_OPER, //21
    CUSTOM_FUNC=255
} OPER_TYPE;

OPER_TYPE resolveFunc(char *);

typedef enum {
    NUM_TYPE, FUNC_TYPE, SYMB_TYPE, COND_TYPE
} AST_NODE_TYPE;

typedef enum { NO_TYPE, INTEGER_TYPE, REAL_TYPE } DATA_TYPE;

typedef struct return_type {
    DATA_TYPE type;
    union {
        double real;
        long integer;
    } value;
} RETURN_TYPE;

typedef struct {
    RETURN_TYPE value;
} NUMBER_AST_NODE;

typedef struct {
    char *name;
    struct ast_node *opList;
    short opNum; /* number of operators */
} FUNCTION_AST_NODE;

typedef struct symbol_ast_node {
    char *name;
} SYMBOL_AST_NODE;

typedef enum { VARIABLE_TYPE, LAMBDA_TYPE, ARG_TYPE } SYMBOL_TYPE;

typedef struct stack_node {
    struct ast_node *val;
    struct stack_node *next;
} STACK_NODE;

typedef struct symbol_table_node {
    SYMBOL_TYPE type;
    DATA_TYPE data_type;
    char *ident;
    struct ast_node *val;
    STACK_NODE *stack;
    struct symbol_table_node *next;
} SYMBOL_TABLE_NODE;

typedef struct {
    struct ast_node *cond;
    struct ast_node *nonzero;
    struct ast_node *zero;
} COND_AST_NODE;

typedef struct ast_node {
    AST_NODE_TYPE type;
    SYMBOL_TABLE_NODE *symbolTable;
    struct ast_node *parent;
    union {
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
        COND_AST_NODE condition;
        SYMBOL_AST_NODE symbol;
    } data;
    struct ast_node *next;
} AST_NODE;

AST_NODE *function(char *funcName, AST_NODE *s_list);
void freeNode(AST_NODE *p);

RETURN_TYPE eval(AST_NODE *ast);

AST_NODE *setSymbolTable(SYMBOL_TABLE_NODE *symbol_table_node, AST_NODE *s_expr);
AST_NODE *symbol (char *name);
SYMBOL_TABLE_NODE *createSymbol(char *type, char *name, AST_NODE *value);
SYMBOL_TABLE_NODE *addSymbolToList(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *newSymbol);
SYMBOL_TABLE_NODE *findSymbol(SYMBOL_TABLE_NODE *symbolTable, SYMBOL_TABLE_NODE *symbol);
SYMBOL_TABLE_NODE *resolveSymbol(char *name, AST_NODE *node);
AST_NODE *real_number(double value);
AST_NODE *integer_number(long value);
DATA_TYPE resolveType(char *typeName);
void printFunc(AST_NODE *p);
AST_NODE *addOpToList(AST_NODE *newOp, AST_NODE *opTable);
RETURN_TYPE multFunc(AST_NODE *p);
RETURN_TYPE addFunc(AST_NODE *p);
AST_NODE *conditional(AST_NODE *cond, AST_NODE *nonzero, AST_NODE *zero);
SYMBOL_TABLE_NODE *createArg(char *name);

#endif
