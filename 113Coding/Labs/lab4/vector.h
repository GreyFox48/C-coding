/**
 * @file vector.h
 * @brief Header file for the fucntions found in vector.h
 * @details See vector.c for implemenation
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h> 		/* for size_t declaration */
/* Place all of your function prototypes here for your Array Problems, #1-8 */
void multiply_array(int a[], size_t size, int n);
void add_array(int a[], size_t size, int n);
void copy_array(int a[], int b[], size_t size);
void add_two_arrays(int a[], int b[], int c[], size_t size);
void product_two_arrays(int a[], int b[], int c[], size_t size);
void inverted_product(int a[], int b[], int c[], size_t size);
void invert_array(int a[], size_t size);
void random_array(int a[], size_t size, int max);
#endif
