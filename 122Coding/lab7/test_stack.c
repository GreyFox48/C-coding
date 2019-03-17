#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void print_empty(stack stk)
{
        if (is_stack_empty(stk))
                printf("stack is empty\n");
        else
                printf("stack is not empty\n");
}

int main(void)
{
        int count;
        int size = 10;
        int *n = NULL;
        int i;
        stack stk = new_stack();
        print_empty(stk);
        
        /* seed rand */
        srand(time(NULL));
        for (i = 0; i < size; i++) {
                n = malloc(sizeof(int));
                assert(n);
                *n = rand() % 101; /*keep random number between [0. 100] */
                push(stk, (void *)n); 
        }


        printf("top of the stack = %d\n", *(int *)peek(stk));
        print_empty(stk);
        
        count = stack_count(stk);
        for (i = 0; i < count; i++) {
                n = (int *)pop(stk);
                printf("%d\n", *n); 
                free(n); 
        }
        print_empty(stk);
        free_stack(stk);
       
        return 0;
}
