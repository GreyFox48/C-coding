/**
 * @file vector_main.c
 * @brief Determines various aspects of hardcoded array values.
 * @details Utalizes each function provided by vector.c, and prints out
 * the determined information.
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None
 * @todo Implement user interface to input arrays and select which
 * function to run.
 */

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void print_array(int a[], size_t size);

int main(void)
{
	int randmax = 50;
	size_t size;
	int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
	int a2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
	int a3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
	int b3[10];
	int a4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
	int b4[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	int c4[10];
	int a5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
	int b5[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	int c5[10];
	int a6[] = {1, 2, 3, 4, 5};
	int b6[] = {6, 7, 8, 9, 10};
	int c6[5];
	int a7[] = {1, 2, 3, 4, 5};
	int a8[10];

	size = sizeof(a1) / sizeof(a1[0]);

        multiply_array(a1, size, 5);
        printf("a1[] = ");
	/* prints array contents in special format */
	print_array(a1, size);
	/* to help seperate each unique function output in terminal */
	puts("");

	add_array(a2, size, 3);
	printf("a2[] = ");
	print_array(a2, size);
	puts("");

	copy_array(a3, b3, size);
	printf("a3[] = ");
	print_array(a3, size);
	printf("b3[] = ");
	print_array(b3, size);
	puts("");

	add_two_arrays(a4, b4, c4, size);
	printf("a4[] = ");
	print_array(a4, size);
	printf("b4[] = ");
	print_array(b4, size);
	printf("c4[] = ");
	print_array(c4, size);
	puts("");

	product_two_arrays(a5, b5, c5, size);
	printf("a5[] = ");
	print_array(a5, size);
	printf("b5[] = ");
	print_array(b5, size);
	printf("c5[] = ");
	print_array(c5, size);
	puts("");

	size = sizeof(a6) / sizeof(a6[0]); /* size redeclated due to new standard array size */

	inverted_product(a6, b6, c6, size);
	printf("a6[] = ");
	print_array(a6, size);
	printf("b6[] = ");
	print_array(b6, size);
	printf("c6[] = ");
	print_array(c6, size);
	puts("");

	invert_array(a7, size);
	printf("a7[] = ");
	print_array(a7, size);
	puts("");

	random_array(a8, size, randmax);
	printf("a8[] = ");
	print_array(a8, size);
	puts("");

	return 0;
}

/** Prints out the elements of a given integer array in a nice format
 * @param a[] the array to be printed
 * @param size the size of a[]
 */
void print_array(int a[], size_t size)
{
	int rep = 0;
	/* first element to be printed is uniquely formatted, thus cannot use for loop */
        printf("{%d,", a[0]);
        for(rep = 1; rep < size - 1; rep++) {
                printf(" %d,", a[rep]);
        }
	/* last element also has unique format */
        printf(" %d}\n", a[size - 1]);
}
