/**
 * @file stack.c
 * @brief Implements a basic stack.
 * @details Stack can holds a void pointer.  Can push, pop, count elements,
 * peek, and free the stack.
 *
 * @date April 24, 2016
 * @author Matthew Olsen
 * @bugs None
 * @todo Nothing
 */ 

#include "stack.h"
#include <stdlib.h>
#include <assert.h>

struct stack_t {
        int count;
        struct node_t {
                void *data;
                struct node_t *next;
        } *head;
};

/**
 * Creates a new stack_t pointer
 */
stack new_stack(void)
{
	struct stack_t *stack = malloc(sizeof(struct stack_t));
	stack->count = 0;	
	stack->head = NULL;
	return stack;
}

/**
 * Pushes a data pointer onto the stack
 * @param stk a pointer to a stack_t stucuture
 * @param data the data to be pushed onto the stack
 */
void push(stack stk, void *data)
{
	struct node_t *temp = malloc(sizeof(struct stack_t));
	temp->data = data;
	temp->next = stk->head;
	stk->head = temp;
}

/**
 * Returns a pointer to the user data by popping top of stack
 * @param stk a pointer to a stack_t structure
 */
void *pop(stack stk)
{
	struct node_t *delete = stk->head;
	void *temp = stk->head->data;
	stk->head = stk->head->next;
	free(delete);
	return temp;
}

/**
 * Returns a void pointer to the top data at the top of the stack
 * @param stk the struct_t to be peeked
 */
void *peek(stack stk)
{
	return stk->head->data;
}

/**
 * Free the given stack_t structure
 * @param stk the stack_t structure to be freed
 */
void free_stack(stack stk)
{
	struct node_t *prev = NULL;
	while (stk->head) {
		prev = stk->head;
		stk->head = stk->head->next;
		free(prev->data);
		free(prev);
	}
	free(stk);
}

/**
 * Determines if the given stack_t structure is empty
 * @param stk the struct_t to determine if empty
 * @return Returns 0 if not empty, and 1 if it is empty
 */
int is_stack_empty(stack stk)
{
	if (!stk->head) {
		return 1;
	}
	return 0;
}

/**
 * Counts the number of elements in the stack
 * @param stk the struct_t to be counted
 * @return the number of elements in the stack
 */
int stack_count(stack stk)
{
	int count = 0;
	struct node_t *temp = stk->head;
	while (temp) {
		count++;
		temp = temp->next;
	}

	return count;
}

