#include "ciProlog.h"

// the knowledge base
// a linked list of propositions
// if a proposition is on the list, it is assumed to be true
// anything not on the list is false
// the first element is empty; it is used as an anchor for kb_head and kb_tail
// we always add at kb_tail
// we always search from kb_head->next;

PROP_TYPE *kb_head, *kb_tail;

void initKnowledgeBase(void)
{
    kb_head = kb_tail = (PROP_TYPE *) malloc(sizeof(PROP_TYPE)); // always empty head of the list
    kb_head->data = ""; // indicates the empty head; skip in searches
    kb_head->next = NULL;
}

void yyerror(char *s)
{
    fprintf(stderr, "yyerror: %s\n", s);
}

bool not(bool logexpr1)
{
    // TODO implement the function
    return !logexpr1;
}

bool and(bool logexpr1, bool logexpr2)
{
    // TODO implement the function

    return (logexpr1 && logexpr2);
}

bool or(bool logexpr1, bool logexpr2)
{
    // TODO implement the function

    return (logexpr1 || logexpr2);
}

// add the assertion to the database
// finding a proposition in the list makes it true
bool assert(char *proposition)
{
    // TODO implement the function
    //return false;
    PROP_TYPE *kb_current = kb_head;
    do {
        kb_current = kb_current->next;
        if (!strncmp(kb_current->data, proposition, strlen(proposition))) {
            return false;
        }
    } while (kb_current != kb_tail);

    kb_current = malloc(sizeof(PROP_TYPE));
    kb_current->data = malloc(sizeof(proposition));
    strncpy(kb_current->data, proposition, strlen(proposition));
    kb_current->next = NULL;
    kb_tail->next = kb_current;
    kb_tail = kb_current;

    return true;
}

// remove the assertion to the database
// after that the proposition is assumed to be false -- it cannot be found
bool retract(char *proposition)
{
    // TODO implement the function
    return false;
}

// find the proposition in the knowledge base
// if found, return true
// otherwise, return false
bool eval(char *proposition)
{
    // TODO implement the function
    return false;
};
