/*
 * Matthew Olsen
 * Lab 6 Parser
 * March 12, 2019
 */

#include "eval.h"
#include "parser.h"

void printProgram(NODE *node)
{
    printf("=> START program\n");
    if (node->leftNode != NULL)
        printStatement(node->leftNode);
    if (node->rightNode != NULL)
        printProgram(node->rightNode);
    printf("=> END program\n");
}

void printStatement(NODE *node)
{
//   TODO: implement
    printf("=> START statement\n");
    if(node->leftNode->type == PRINT_STMT_NODE) {
        printPrintStmt(node->leftNode);
    } else if(node->leftNode->type == REPEAT_STMT_NODE) {
        printRepeatStmt(node->leftNode);
    } else if(node->leftNode->type == ASSIGN_STMT_NODE) {
        printAssignStmt(node->leftNode);
    } else {
        error("printStatement received invalid node type.");
    }

    printf("=> END statement\n");

}

void printAssignStmt(NODE *node)
{
//   TODO: implement
    printf("=> START assignment\n");
    if (node->leftNode != NULL)
        printId(node->leftNode);
    if (node->rightNode != NULL)
        printExpr(node->rightNode);
    printf("=> END assignment\n");
}

void printRepeatStmt(NODE *node)
{
//   TODO: implement
    printf("=> START repeat\n");
    if (node->leftNode != NULL)
        printExpr(node->leftNode);
    if (node->rightNode != NULL)
        printStatement(node->rightNode);
    printf("=> END repeat\n");
}

void printPrintStmt(NODE *node)
{
//   TODO: implement
    printf("=> START print\n");
    if (node->leftNode != NULL)
        printExpr(node->leftNode);
    printf("=> END print\n");
}

void printExpr(NODE *node)
{
//   TODO: implement
    printf("=> START expression\n");
    if (node->leftNode != NULL)
        printTerm(node->leftNode);
    if (node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    printf("=> END expression\n");
}

void printTerm(NODE *node)
{
//   TODO: implement
    printf("=> START term\n");
    if (node->leftNode != NULL)
        printFactor(node->leftNode);
    if (node->rightNode != NULL) {
        printf("%c\n", node->data.op);
        printExpr(node->rightNode);
    }
    printf("=> END term\n");
}

void printFactor(NODE *node)
{
//   TODO: implement
    printf("=> START factor\n");
    if(node->leftNode->type == IDENTIFIER_NODE) {
        printId(node->leftNode);
    } else if(node->leftNode->type == NUMBER_NODE) {
        printNumber(node->leftNode);
    } else if(node->leftNode->type == FACTOR_NODE) {
        printf("-\n");
        printFactor(node->leftNode);
    } else if(node->leftNode->type == EXPR_NODE) {
        printExpr(node->leftNode);
    } else {
        error("printFactor received invalid node type.");
    }

    printf("=> END factor\n");
}

void printId(NODE *node)
{
//   TODO: implement
    printf("=> START identifier\n");
    printf("<id> %s\n", node->data.identifier);
    printf("=> END identifier\n");
}

void printNumber(NODE *node)
{
//   TODO: implement
    printf("=> START number\n");
    printf("<number> %lf\n", node->data.number);
    printf("=> END number\n");
}

