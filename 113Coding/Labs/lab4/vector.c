/**
 * @file vector.c
 * @brief Implements various array functions.
 * @details adds or multiplies a constant to an array's elements, mulitpies
 *  or adds two arrays together into a third, copies an array into a second, finds
 * the product of two arrays when multiplied in inverted order, or fills an array
 * with random integers.
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None
 * @todo Write equivalent functions for floating point numbers
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vector.h"

/* Place all of your functions here for your Array Problems */
/**
 * Multiplies each element of the array by a given constant
 * @param a[] the array holding elements to be multiplied
 * @param size_t the length of a[]
 * @param n the constant to multiply each element with
 */
void multiply_array(int a[], size_t size, int n) {
        int rep;
        for(rep = 0; rep < size; rep++){
                /* finds product of each array element with a constant */
                a[rep] *= n;
        }
}

/**
 * Adds a given constant to each element of an array
 * @param a[] the array with elements to be added to
 * @param size_t the length of a[]
 * @param n the constant to add to each element
 */
void add_array(int a[], size_t size, int n) {
        int rep;
        for(rep = 0; rep < size; rep++){
                /* adds constant to each array element */
                a[rep] += n;
        }
}

/**
 * Copies the elements of one array into another arrray
 * @param a[] the array containing the elements to be copied
 * @param b[] the array to be copied to
 * @param size the size of both arrays
 */
void copy_array(int a[], int b[], size_t size) {
        int rep;
        for(rep = 0; rep < size; rep++){
                b[rep] = a[rep];
        }
}

/**
 * Adds the elements of two arrays into a third
 * @param a[] first of two arrays to be added
 * @param b[] second of two arrays to be added
 * @param c[] array to hold sum of the two arrays
 */
void add_two_arrays(int a[], int b[], int c[], size_t size) {
        int rep;
        for(rep = 0; rep < size; rep++){
                c[rep] =  a[rep] + b[rep];
        }
}

/**
 * Adds product of two arrays into a third
 * @param a[] first of two arrays to be multiplied
 * @param b[] second of two arrays to be multiplied
 * @param c[] array to hold product of the two arrays
 */
void product_two_arrays(int a[], int b[], int c[], size_t size) {
        int rep;
        for(rep = 0; rep < size; rep++) {
                c[rep] =  a[rep] * b[rep];
        }
}

/**
 * Adds the inverted product of two arrays into a third
 * @param a[] first of two arrays to be multiplied
 * @param b[] second of two arrays to be multiplied
 * @param c[] array to hold product of the two arrays
 */
void inverted_product(int a[], int b[], int c[], size_t size) {
        int rep;
        for(rep = 0; rep < size; rep++) {
                c[rep] =  a[rep] * b[(size - 1) - rep]; /* -1 hardcoded to prevent out of bounds array */
        }
}

/**
 * Invertes the elements of two arrays
 * @param a[] the array containing the elements to be inverted
 * @param size the size of array a[]
 */
void invert_array(int a[], size_t size) {
        int rep;
        int temp;
        /* (size -1) / 2 stops at midpoint or element before to prevent repeated swap */
        for(rep = 0; rep < (size - 1) / 2; rep++) {
                temp = a[rep];
                a[rep] =  a[(size - 1) - rep];
                a[(size - 1) - rep] = temp;
        }
}

/**
 * Creates an array full of random integers, from [0, max]
 * @param a[] the array to be populated with random integers
 * @param size the length of array a[]
 * @param max the maximum integer that could be randomized
 */
void random_array(int a[], size_t size, int max) {
        int rep;
        /* seed value for random() seen later */
        srandom(time(NULL));
        for(rep = 0; rep < size; rep++) {
                a[rep] = random() % (max + 1); /* +1 ensure range is inclusive of max */
        }
}
