/**
 * @file array.c
 * @brief Implements and prints various array funtions.
 * @details Funtions include array printing, incrementing an array's elements
 * by one, and adding two arrays togther.
 *
 * @author Matthew Olsen
 * @date 2015-10-28
 * @bug None
 * @todo Nothing
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Prints the elements of an integer array.  Array based version.
 * @param a the array to be printed
 * @param len the length of the array
 */
void print_array(int *a, size_t len)
{
	int i = 0;

	for ( ;i < len;i++)
		printf(i == len - 1 ? "%d\n" : "%d ", a[i]);
}

/**
 * Prints the elements of an integer array.
 * Pointer arthimetic version of print_array.
 * @param a the array to be printed
 * @param len the length of the array
 */
void print_parray(int *a, size_t len)
{
	int i = 0;

	for ( ;i < len;i++)
		printf(i == len - 1 ? "%d\n" : "%d ", *(a + i));

}

/**
 * Increments the elements of an integer array by one.  Array based version.
 * @param a the array to be incremented by one
 * @param len the length of the array
 */
void inc_array(int *a, size_t len)
{
	int i = 0;

	for ( ; i < len; i++)
		a[i]++;
}

/**
 * Increments the elements of an integer array by one.
 * Pointer based version of inc_array.
 * @param a the array to be incremented by one.
 * @param len the length of the array
 */
void inc_parray(int *a, size_t len)
{
	int i = 0;
	int *p = a;

	for ( ; i < len; i++, p++)
		(*p)++;

}


/**
 * Adds the corresponding elements of two integer arrays and places the sum
 * into the first.  Array based version.
 * @param a the array to be added to.
 * @param b the array to add elements to a
 * @param len the length of both of the arrays
 */
void add_arrays(int *a, int *b, size_t len)
{
	int i = 0;

	for (; i < len; i++)
		a[i] += b[i];
}

/**
 * Adds the corresponding elements of two integer arrays and places the sum
 * into the first.  pointer version of add_arrays a = a + b
 * @param a the array to be added to.
 * @param b the array to add elements to a
 * @param len the length of both of the arrays
 */
void add_parrays(int *a, int *b, size_t len)
{
	int i = 0;
	int *p = a;
	int *j = b;

	for (; i < len; i++, p++, j++)
		*p += *j;
}


int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int b[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

	size_t len_a = sizeof(a)/sizeof(int);
	size_t len_b = sizeof(b)/sizeof(int);

	printf("a = ");
	print_array(a, len_a);
	print_parray(a, len_a);

	printf("\nb = ");
	print_array(b, len_b);
	print_parray(b, len_b);

	inc_array(a, len_a);
	printf("\nafter incrementing\na = ");
	print_array(a, len_a);
        inc_parray(a, len_a);
	print_parray(a, len_a);

	print_array(a, len_a);
	if (len_a != len_b) 	/* assume arrays are of the same length */
		exit(EXIT_FAILURE);
	else
		add_arrays(a, b, len_a);
		add_parrays(a, b, len_b);

	printf("\na = a + b\na = ");
	print_array(a, len_a);
	print_parray(a, len_a);
	printf("\nb remains unchanged\nb = ");
	print_array(b, len_b);
	print_parray(b, len_b);

	return 0;
}
