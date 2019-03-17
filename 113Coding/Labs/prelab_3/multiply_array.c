/**
 * @file multiply_array.c
 * @brief prints the product of the array elements between the inputed start and stop points  
 *
 * @author Matthew Olsen
 * @date September 19th 2015 
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int array_multiply_range(int a[], size_t size, int start, int stop);

int main(void)
{
        int start;
        int stop;     
        int a[] = {6, 3, 5, 2, 3, 2, 4};
        size_t size = sizeof(a) / sizeof(a[0]);
        char s[SIZE];

        printf("Please enter the start: ");
        fgets(s, SIZE - 1, stdin);
        start = atoi(s);

        printf("And now the stop: ");
        fgets(s, SIZE - 1, stdin);
        stop = atoi(s);               

        printf("The product is %d.\n", array_multiply_range(a, size, start, stop));

        return 0;
}

/**
 * finds the product of the array elements between start and stop
 * @param a[] the array with the elements to multiply
 * @param size the size of the array
 * @param start the number of the array element to start multiplication at
 * @param stop the number of the array element to stop multiplication at
 * @return the product of the array elements
 */
int array_multiply_range(int a[], size_t size, int start, int stop)
{
        /* ensures stop or start are within bounds */
        if(start < 0) {
                start = 0;
        } 
        if (stop < 0) {
                stop = 0;
        } 
        if (start > size - 1) {
                start = size - 1;
        } 
        if (stop > size - 1) {
                stop = size - 1;
        }

        int product = 1;

        do {
                product = product * a[start];
                start++;
        } while (start <= stop);

        return product;
}
