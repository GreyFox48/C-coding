/*
 * Name: Matthew Olsen
 * Lab: Lab 4 Lexical Analysis
 * Date: 02/20/18
 */

#include "scanner.h"

/*
 * SUBMIT THE FSM!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */


TOKEN *ungottenToken = NULL; // used by parser

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
    if (token == NULL)
        return;

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
bool isKeyword(TOKEN *token, char *str) {
    if (strcmp(str, "repeat") == 0)
        token->type = REPEAT_TOKEN;
    else if (strcmp(str, "print") == 0)
        token->type = PRINT_TOKEN;
    else
        return false;

    return true;
}

//
// scan input for a token using the nested case method
//
TOKEN *scannerNestedCases() {

    if (ungottenToken != NULL) {
        TOKEN *tok = ungottenToken;
        ungottenToken = NULL;
        return tok;
    }


    // temporary buffer for collecting characters
    char tempString[BUF_SIZE];

    // acquire space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN; // assume that the token is invalid to start with
    token->strVal = NULL;

    // analyze the input character by character figuring out what kind of token they constitute
    char c;
    int i = 0;
    int state = 1;
    while ((token->type == INVALID_TOKEN) && ((c = getchar()))) {
        switch (state) {
            case 1:
                switch (c) {
                    case '*':
                        /* ventures toward ad hoc but prevents wordy code */
                        token->type = MULT_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;

                    case '+':
                        token->type = PLUS_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case '-':
                        token->type = MINUS_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case '/':
                        token->type = DIV_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case '%':
                        token->type = MOD_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case '(':
                        token->type = LPAREN_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case ')':
                        token->type = RPAREN_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case ';':
                        token->type = SEMICOLON_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case '=':
                        token->type = ASSIGNMENT_TOKEN;
                        token->strVal = malloc(sizeof(char) + 1);
                        token->strVal[0] = c;
                        token->strVal[1] = '\0';
                        return token;
                    case EOF:
                        token->type = END_OF_INPUT_TOKEN;
                        token->strVal = malloc((strlen("EOF") * sizeof(char)) + 1);
                        strncpy(token->strVal, "EOF", 4);
                        return token;
                    case '0'...'9':
                        state = 12;
                        // want to read all of it in the case statement
                        ungetc(c, stdin);
                        break;
                    case 'a'...'z':
                        state = 13;
                        ungetc(c, stdin);
                        break;
                    case ' ': // skip whitespace
                    case '\t':
                    case '\n':
                        break;
                        //default:
                        //puts("wat");
                }
                break;
            case 12:
                switch (c) {
                    case '0'...'9':
                        tempString[i++] = c;
                        break;
                    default:
                        ungetc(c, stdin);
                        tempString[i] = '\0';
                        token->type = NUMBER_TOKEN;
                        token->strVal = malloc(strlen(tempString) + 1);
                        strcpy(token->strVal, tempString);
                        return token;
                }
                break;
            case 13:
                switch (c) {
                    case 'a'...'z':
                        tempString[i++] = c;
                        break;
                    default:
                        ungetc(c, stdin);
                        tempString[i] = '\0';
                        if (!isKeyword(token, tempString)) {
                            token->type = IDENT_TOKEN;
                            token->strVal = malloc(strlen(tempString) + 1);
                            strcpy(token->strVal, tempString);
                        }
                        return token;
                }
                break;

        }
    }
}