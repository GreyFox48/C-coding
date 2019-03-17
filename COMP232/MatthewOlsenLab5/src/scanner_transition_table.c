/*
 * Name: Matthew Olsen
 * Lab: Lab 5 State Transition Table Scanner
 * Date: 03/02/19
 */

#include "scanner.h"

#define BUFFER_SIZE 256


TOKEN *ungottenToken = NULL; // may be used by parser in the next lab

//
// return token to the input, so it can be analyzed again
//
void ungetToken(TOKEN **token) {
    ungottenToken = *token;
    *token = NULL;
}

//
// clean up the token structure
//
void freeToken(TOKEN **token) {
    if (*token == NULL)
        return;

    if ((*token)->strVal != NULL)
        free((*token)->strVal);

    free(*token);

    *token = NULL;
}

//
// check if a collected sequence of characters is a keyword
//
void updateTypeIfKeyword(TOKEN *token) {
// TODO Implement the function
    if (!strcmp(token->strVal, "repeat")) {
        token->type = REPEAT;
        free(token->strVal); /* no use in keeping this */
        token->strVal = NULL;
    } else if (!strcmp(token->strVal, "print")) {
        token->type = PRINT;
        free(token->strVal); /* no use in keeping this */
        token->strVal = NULL;
    }
}


TRANS_TABLE_TYPE *scanInit() {
    char buff[BUFFER_SIZE];
    char word[BUFFER_SIZE];
    TRANS_TABLE_TYPE *returnTable = NULL;
    int i = 0, j = 0, x = 0;
    char *tok = NULL;
    char c;
    char *bp = buff;

// TODO Implement the function
    /* populate numberOfStates and numberOfClasses */
    returnTable = malloc(sizeof(TRANS_TABLE_TYPE));
    returnTable->table = NULL;
    returnTable->inputSymbolClasses = NULL;
    scanf("%[^\n]\n", buff);
    sscanf(buff, "%d %d", &(returnTable->numberOfStates), &(returnTable->numberOfClasses));
    returnTable->numberOfClasses += 2; /* one for invalid states and one for a column of return  */

    /* populate inputSymbolClasses */
    scanf("%[^\n]\n", buff);
    returnTable->inputSymbolClasses = malloc(returnTable->numberOfClasses * sizeof(char *));
    for (i = 0; i < returnTable->numberOfClasses; i++) {
        returnTable->inputSymbolClasses[i] = NULL;
    }
    i = 0;
    while (tok = strsep(&bp, ",")) {
        while (c = tok[i++]) {
            switch (c) {
                case '\\':
                    c = tok[i++]; /* need to look ahead to next character after escape */
                    if (c == 'n') {
                        word[j++] = '\n';
                    } else if (c == 't') {
                        word[j++] = '\t';
                    } else {
                        printf("Error: file %s line %d\n", __FILE__, __LINE__);
                        printf("\tInvalid character after escape character.\n");
                    }
                    break;
                default:
                    word[j++] = c;
            }
        }
        word[j] = '\0'; /* ensure it ends */
        returnTable->inputSymbolClasses[x] = malloc(strlen(word) + 1);
        strncpy(returnTable->inputSymbolClasses[x++], word, strlen(word) + 1);
        i = 0;
        j = 0;
    }

    /* init the table */
    returnTable->table = malloc(returnTable->numberOfStates * sizeof(char *));
    for (i = 0; i < returnTable->numberOfStates; i++) {
        returnTable->table[i] = malloc(returnTable->numberOfClasses * sizeof(char));
    }
    /* read the table */
    for (i = 0; i < returnTable->numberOfStates; i++) {
        scanf("%[^\n]\n", buff); /* read the row */
        bp = buff;
        for (j = 0; j < returnTable->numberOfClasses; j++) {
            /* get each  entry*/
            tok = strsep(&bp, " ");
            if (!strcmp(tok, "a")) {
                returnTable->table[i][j] = 'a';
            } else if (!strcmp(tok, "e")) {
                returnTable->table[i][j] = 'e';
            } else {
                returnTable->table[i][j] = atoi(tok);
            }
        }
    }

    return returnTable;
}

int findIndexToClass(TRANS_TABLE_TYPE *transitionTable, char c) {
    // TODO Implement the function
    int class;
    for (class = 0; class < transitionTable->numberOfClasses - 2; class++) {
        if (strchr(transitionTable->inputSymbolClasses[class], c)) {
            return class;
        }
    }


    return transitionTable->numberOfClasses - 2; /*if nothing found then it is the error class */
}

TOKEN *scanner(TRANS_TABLE_TYPE *transitionTable) {
    TOKEN *token = NULL;
    char buffer[BUFFER_SIZE];
    int state = 0;
    int bindex = 0;
    int row = 0;
    int class = 0;
    char c = 0;

    while (1) {
        c = getc(stdin);
        class = findIndexToClass(transitionTable, c);
        row = state;

        state = transitionTable->table[row][class];
        /* if we have left the end state, record what the character is.
         * used to skip whitespace */
        if (state != 0) {
            buffer[bindex++] = c;
        }

        switch (state) {
            case 'a':
                token = malloc(sizeof(TOKEN));
                token->strVal = NULL;
                ungetc(c, stdin);
                buffer[bindex - 1] = '\0'; /* -1 to overwrite last character not part of accepted token */
                token->type = transitionTable->table[row][transitionTable->numberOfClasses - 1];
                if (token ->type == IDENT_TOKEN || token->type == NUMBER_TOKEN) {
                    token->strVal = malloc(strlen(buffer) * (sizeof(char) + 1));
                    strncpy(token->strVal, buffer, strlen(buffer) + 1);
                }
                if (token->type == IDENT_TOKEN) {
                    updateTypeIfKeyword(token);
                }

                return token;
            case 'e':
                token = malloc(sizeof(TOKEN));
                token->strVal = NULL;
                /* easy to consider EOF as a special case of invalid */
                if (c == EOF) {
                    token->type = END_OF_INPUT_TOKEN;
                    return token;
                }
                buffer[bindex] = '\0';
                token->strVal = malloc(strlen(buffer) * (sizeof(char) + 1));
                strncpy(token->strVal, buffer, strlen(buffer) + 1);
                token->type = transitionTable->table[row][transitionTable->numberOfClasses - 1];
                return token;
            default:
                break;
        }
    }

}

void freeTransTable(TRANS_TABLE_TYPE **tTable) {
    int i;
    for (i = 0; i < (*tTable)->numberOfStates; i++) {
        free((*tTable)->table[i]);
    }
    free((*tTable)->table);

    for (i = 0; i < (*tTable)->numberOfClasses; i++) {
        free((*tTable)->inputSymbolClasses[i]);
    }
    free((*tTable)->inputSymbolClasses);

    free(*tTable);
}



