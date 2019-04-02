/**
 * Matthew Olsen
 * April 2, 2019
 * Comp 232L Lab 8 Introduction to Bison
 * Bugs: Provied code at ciProlog.l line 20 lacked a null terminator and the
 * space for one.  I edited it.  Hopefully, valgrind is now happy.
 */

#include "ciProlog.h"

// the knowledge base
// a linked list of propositions
// if a proposition is on the list, it is assumed to be true
// anything not on the list is false
// the first element is empty; it is used as an anchor for kb_head and kb_tail
// we always add at kb_tail
// we always search from kb_head->next;

PROP_TYPE *kb_head, *kb_tail;

void initKnowledgeBase(void) {
    kb_head = kb_tail = (PROP_TYPE *) malloc(sizeof(PROP_TYPE)); // always empty head of the list
    kb_head->data = ""; // indicates the empty head; skip in searches
    kb_head->next = NULL;
}

void yyerror(char *s) {
    fprintf(stderr, "yyerror: %s\n", s);
}

bool not(bool logexpr1) {
    // TODO implement the function
    return !logexpr1;
}

bool and(bool logexpr1, bool logexpr2) {
    // TODO implement the function

    return (logexpr1 && logexpr2);
}

bool or(bool logexpr1, bool logexpr2) {
    // TODO implement the function

    return (logexpr1 || logexpr2);
}

// add the assertion to the database
// finding a proposition in the list makes it true
bool assert(char *proposition) {
    // TODO implement the function
    //return false;
    PROP_TYPE *kb_current = kb_head;

    while (kb_current != kb_tail) {
        kb_current = kb_current->next;
        if (!strncmp(kb_current->data, proposition, strlen(proposition))) {
            free(proposition);
            return false;
        }
    }

    kb_current = malloc(sizeof(PROP_TYPE));
    kb_current->data = malloc(sizeof(char) * (strlen(proposition) + 1));
    strncpy(kb_current->data, proposition, strlen(proposition));
    kb_current->next = NULL;
    kb_tail->next = kb_current;
    kb_tail = kb_current;

    /* proposition allocations do not have a free embedded anywhere in the
     * provided code, so I added one wherever I handle one.
     */
    free(proposition);
    return true;
}

// remove the assertion to the database
// after that the proposition is assumed to be false -- it cannot be found
bool retract(char *proposition) {
    // TODO implement the function
    PROP_TYPE *kb_current = kb_head->next;
    PROP_TYPE *kb_previous = kb_head;

    while (kb_current != NULL) {
        if (!strncmp(kb_current->data, proposition, strlen(proposition))) {
            if (kb_current == kb_tail) {
                kb_tail = kb_previous;
                kb_tail->next = NULL;
                free(kb_current->data);
                free(kb_current);
            } else {
                kb_previous->next = kb_current->next;
                free(kb_current->data);
                free(kb_current);
            }
            free(proposition);
            return true;
        }
        kb_previous = kb_current;
        kb_current = kb_current->next;
    }

    /* otherwise wasn't found */
    free(proposition);
    return false;
}

// find the proposition in the knowledge base
// if found, return true
// otherwise, return false
bool eval(char *proposition) {
    // TODO implement the function
    PROP_TYPE *kb_current = kb_head->next;

    while (kb_current != NULL) {
        if (!strncmp(kb_current->data, proposition, strlen(proposition))) {
            free(proposition);
            return true;
        }
        kb_current = kb_current->next;
    }
    free(proposition);
    return false;
};

// exit and ensure header node and remaining nodes are gone
void deleteKnowledgeBase() {
    PROP_TYPE *kb_current = kb_head;
    PROP_TYPE *kb_next = kb_head->next;
    while (kb_next != NULL) {
        free(kb_current->data);
        free(kb_current);
        kb_current = kb_next;
        kb_next = kb_current->next;
    }
    free(kb_current->data);
    free(kb_current);
}