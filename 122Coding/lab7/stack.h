/**
 * @file stack.h
 * @brief Implements a basic stack.
 * @details See stack.c for implementation.
 *
 * @date April 24, 2016
 * @author Matthew Olsen
 * @bugs None
 * @todo Nothing
 */ 

#ifndef _STACK_H_
#define _STACK_H_


typedef struct stack_t *stack;

stack new_stack(void);
void push(stack stk, void *data);
void *pop(stack stk); 
void *peek(stack stk);
void free_stack(stack stk);
int is_stack_empty(stack stk);
int stack_count(stack stk);

#endif
