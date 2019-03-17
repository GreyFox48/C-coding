/**
 * @file divisor.c
 * @brief Prints out a number along with 0 or 1 on the same line, depending on if the
 * array element was divisible for divisor.
 * @details the numbers to be checked and the results are stored on two different 
 * arrays of the same size. 
 *
 * @author Matthew Olsen
 * @date September 19th 2015  
 */

#include <stdio.h>

void array_mod(int a[], int div[], size_t size, int divisor);

void print_array(int a[], int div[], size_t size);
 
int main(void)
{
        int a[] = {13, 44, 85, 23, 72, 99, 100, 108, 222, 1084};
        size_t size = sizeof(a) / sizeof(a[0]);
        int div[size];
        int divisor = 4;        
        
        array_mod(a, div, size, divisor);
        print_array(a, div, size);

        return 0;
}

/**
 * checks whether element from a[] is divisible by divisor, and stores 1 in in div[] if true, 0 if false 
 * @param a[] the array that contains the numbers to be checked
 * @param div[] array of same size of a[] that contains 0 or 1 depending on whether element from a[] was divisble by divisor
 * @param size the size of both array a[] and div[]
 * @param divisor the number to be used to divide elements of array a[]
 */
void array_mod(int a[], int div[], size_t size, int divisor)
{
        int rep;
        for (rep = 0; rep < size; rep++) {
                if ((a[rep] % divisor) == 0) {
                        div[rep] = 1;
                } else {
                        div[rep] = 0;
                }
        } 
}

/**
 * prints out elements of a[], on one line each along with corresponding element of div[] 
 * @param a[] the array that contains the numbers to be checked
 * @param div[] array of same size of a[] that contains 0 or 1 depending on whether element from a[] was divisble by divisor
 * @param size the size of both array a[] and div[]
 */
void print_array(int a[], int div[], size_t size)
{
        int rep;        
        for(rep = 0; rep < size; rep++) {
                printf("%d\t%d\n", a[rep], div[rep]);
        }
}
