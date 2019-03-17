/**
 * @file russian.c
 * @brief Implements russian peasant algorithm.
 * @details Reads in two integers in "x y" format, and prints out the product
 * of x and y in a standarized format.
 *
 * @date March 5, 2016
 * @author Matthew Olsen
 * @bug None
 * @todo Nothing
 */

#include <stdio.h>
#include <math.h>

int russian(int x, int y);

#define LEN 1024

int main(void)
{
        char in[LEN];
        int x, y, product;
                
        /* get and print input */
        while(fgets(in, LEN, stdin)) {
                sscanf(in, "%d %d", &x, &y);
                product = russian(x, y);
                printf("%d * %d = %d\n", x, y , product);
        }

        return 0;
}

/**
 * Calculates the product of x and y, using the "russian peasant algorithm"
 * @param x the first term
 * @param y the second term
 * @return the product of terms x and y
 */
int russian(int x, int y)
{
        int product = 0;
        int n; 
        
        /* >= 1 to ensure base case executes */
        for(n = 0; y >= 1; y /= 2, n++) {
                if (y % 2 == 1) {
                        product += x * pow(2, n);
                }
        } 
        
        return product;
}

