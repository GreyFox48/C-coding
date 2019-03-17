/**
 * @file swap.c
 * @brief Swaps two integer values using pointers.
 *
 * @author Matthew Olsen
 * @date 2015-10-28 
 */

#include <stdio.h>

void print_vars(int a, int b)
{
	printf("a = %d\tb = %d\n", a, b);
}

/* a first try at writing a swap function */
/* swap the contents a with b and b with a */
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;

	printf("in function swap: ");
	print_vars(*a, *b);
}

int main(void)
{
	int a = 6;
	int b = 9;
	printf("before swap: ");
	print_vars(a,b);

	swap(&a, &b);

	printf("after swap: ");
	print_vars(a,b);

	return 0;
}
