/**
 * @file multiply.c
 * @brief prints the product of integers between the input of start and stop, inclusive
 *
 * @author Matthew Olsen
 * @date September 19th 2015 
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
int main(void)
{
        int start;
        int stop;
        int product = 1;
        char s[SIZE];

        printf("Please enter the start: ");
        fgets(s, SIZE - 1, stdin);
        start = atoi(s);

        printf("And now the stop: ");
        fgets(s, SIZE - 1, stdin);
        stop = atoi(s);

        /* garuntees a product is printed if start is less than stop */
        do {
                product = product * start;
                start++;
        } while (start <= stop);

        printf("The product is %d.\n", product);

        return 0;
}
