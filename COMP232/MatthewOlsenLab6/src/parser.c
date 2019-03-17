/*
 * Matthew Olsen
 * Lab 6 Parser
 * March 12, 2019
 */

#include "parser.h"

TOKEN *getNextToken(TOKEN **token) {
    freeToken(token);
    return scannerAdHoc();
}

NODE *program() {
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = PROGRAM_NODE;
    node->leftNode = statement();
    if (node->leftNode == NULL) {
        free(node);
        return NULL;
    } else {
        node->rightNode = program();
    }
    /*
    if (node->leftNode != NULL)
        node->rightNode = program();
    return node;
     */

    return node;
}

NODE *statement() {
    //   TODO: implement

    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = STATEMENT_NODE;
    TOKEN *token = getNextToken(NULL);
    char buff[MAX_LINE_LENGTH];

    if (token->type == IDENT_TOKEN) {
        node->leftNode = assignStmt(&token);
    } else if (token->type == REPEAT_TOKEN) {
        node->leftNode = repeatStmt(&token);
    } else if (token->type == PRINT_TOKEN) {
        node->leftNode = printStmt(&token);
    } else if (token->type == END_OF_INPUT_TOKEN) {  /* END_OF_INPUT processing */
        free(node);
        freeToken(&token);
        return NULL;
    } else {
        sprintf(buff, "Expected an identifier, \"repeat\", or a \"print\"."
                      "  Got a token type of %u instead.  Thanks...", token->type);
        error(buff);
    }
    node->rightNode = NULL;

    freeToken(&token);
    return node;

}

NODE *assignStmt(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = ASSIGN_STMT_NODE;
    node->leftNode = id(currToken);
    char buff[MAX_LINE_LENGTH];

    *currToken = getNextToken(currToken);
    if ((*currToken)->type != ASSIGNMENT_TOKEN) {
        sprintf(buff, "Expected an \"=\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }

    (*currToken) = getNextToken(currToken);
    node->rightNode = expr(currToken);

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type != SEMICOLON_TOKEN) {
        sprintf(buff, "Expected an \";\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }

    freeToken(currToken);
    return node;
}

NODE *repeatStmt(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = REPEAT_STMT_NODE;
    char buff[MAX_LINE_LENGTH];

    /* we already know it begins with "repeat" if sent here, so move on. */
    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type != LPAREN_TOKEN) {
        sprintf(buff, "Expected an \"(\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }

    (*currToken) = getNextToken(currToken);
    node->leftNode = expr(currToken);

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type != RPAREN_TOKEN) {
        sprintf(buff, "Expected an \")\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }


    /* free the current because statement does not receive current */
    freeToken(currToken);

    node->rightNode = statement();

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type != SEMICOLON_TOKEN) {
        sprintf(buff, "Expected an \";\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }

    freeToken(currToken);
    return node;
}

NODE *printStmt(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = PRINT_STMT_NODE;
    char buff[MAX_LINE_LENGTH];

    /* we already know it begins with "print" if sent here, so move on. */
    (*currToken) = getNextToken(currToken);
    node->leftNode = expr(currToken);

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type != SEMICOLON_TOKEN) {
        sprintf(buff, "Expected an \";\"."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }

    freeToken(currToken);
    return node;
}

NODE *expr(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = EXPR_NODE;

    node->leftNode = term(currToken);

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type == PLUS_TOKEN) {
        node->data.op = '+';
        (*currToken) = getNextToken(currToken);
        node->rightNode = expr(currToken);
    } else if ((*currToken)->type == MINUS_TOKEN) {
        node->data.op = '-';
        (*currToken) = getNextToken(currToken);
        node->rightNode = expr(currToken);
    } else /* expr only is one term */ {
        ungetToken(currToken);
        node->rightNode = NULL;
    }

    return node;
}

NODE *term(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = TERM_NODE;

    node->leftNode = factor(currToken);

    (*currToken) = getNextToken(currToken);
    if ((*currToken)->type == MULT_TOKEN) {
        node->data.op = '*';
        (*currToken) = getNextToken(currToken);
        node->rightNode = expr(currToken);
    } else if ((*currToken)->type == DIV_TOKEN) {
        node->data.op = '/';
        (*currToken) = getNextToken(currToken);
        node->rightNode = expr(currToken);
        /* its only an expression */
    } else if ((*currToken)->type == MOD_TOKEN) {
        node->data.op = '%';
        (*currToken) = getNextToken(currToken);
        node->rightNode = expr(currToken);
        /* its only an expression */
    } else /* expr only is one factor */{
        ungetToken(currToken);
        node->rightNode = NULL;
    }

    return node;
}

NODE *factor(TOKEN **currToken) {
//   TODO: implement
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = FACTOR_NODE;
    char buff[MAX_LINE_LENGTH];

    if ((*currToken)->type == IDENT_TOKEN) {
        node->leftNode = id(currToken);
        node->rightNode = NULL;
    } else if ((*currToken)->type == NUMBER_TOKEN) {
        node->leftNode = number(currToken);
        node->rightNode = NULL;
        /* its only an expression */
    } else if ((*currToken)->type == MINUS_TOKEN) {
        node->data.op = '-';

        (*currToken) = getNextToken(currToken);
        node->leftNode = factor(currToken);
        node->rightNode = NULL;
    } else if ((*currToken)->type == LPAREN_TOKEN) {
        (*currToken) = getNextToken(currToken);
        node->leftNode = expr(currToken);
        node->rightNode = NULL;

        (*currToken) = getNextToken(currToken);
        if ((*currToken)->type != RPAREN_TOKEN) {
            sprintf(buff, "Expected an \")\"."
                          "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
            error(buff);
        }

    } else {
        sprintf(buff, "Expected an identifier, number, negative factor token, or a ( expression )."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }
    return node;
}

NODE *id(TOKEN **currToken) {
//   TODO: implement
    char buff[MAX_LINE_LENGTH];

    if ((*currToken)->type != IDENT_TOKEN) {
        sprintf(buff, "Expected an identifier."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = IDENTIFIER_NODE;
    node->leftNode = NULL;
    node->rightNode = NULL;
    strncpy(node->data.identifier, (*currToken)->strVal, strlen((*currToken)->strVal) + 1);

    return node;
}

NODE *number(TOKEN **currToken) {
    //   TODO: implement
    char buff[MAX_LINE_LENGTH];

    if ((*currToken)->type != NUMBER_TOKEN) {
        sprintf(buff, "Expected an identifier."
                      "  Got a token type of %u instead.  Thanks...", (*currToken)->type);
        error(buff);
    }
    NODE *node = malloc(sizeof(NODE));
    node->leftNode = NULL;
    node->rightNode = NULL;

    node->type = NUMBER_NODE;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->data.number = strtod((*currToken)->strVal, NULL);
    return node;
}

void freeNodeTree(NODE *node) {
    if (node->leftNode != NULL) {
        freeNodeTree(node->leftNode);
    }
    if (node->rightNode != NULL) {
        freeNodeTree(node->rightNode);
    }
    free(node);
}

void error(char *errorMessage) {
    printf("PARSING ERROR: %s\nExiting...\n", errorMessage);
    exit(1);
}

