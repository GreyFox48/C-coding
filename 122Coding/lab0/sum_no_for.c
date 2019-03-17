/**
 * @file sum_no_for.c
 * @brief determines the sum of the sequence 1 + 2 + ... + (3n - 1), where n
 * is the number of integers in the sequence
 * @details utalizes an equation to determine the sum
 *
 * @author Matthew Olsen
 * @date February 7, 2016
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

unsigned long long sum_no_for(unsigned long long n);

int main(int argc, char **argv)
{
        unsigned long long num; /* the largest number in the sequence */
        unsigned long long sum = 0;
        int power = 0; /* to help increment num later */
        clock_t start, stop; /* to measure time it takes to process each num */
        
        for (power = 0; power < 10; power++) {
                num = pow(10, power);
                start = clock();
                sum = sum_no_for(num);
                stop = clock();
                /* size of n|total sum| time took */
                printf("%llu|%llu|%3.24lf\n"
                ,num , sum, (double) (stop - start) / CLOCKS_PER_SEC);
        }
        return 0;
}
/**
 * Determines the sum of the number sequence 2 + 3 + .. + (3n - 1), where n is
 * the number of intergers to sum utilizing the equation 3n(n + 1)/2 - n
 * @param n the number of intergers in the sequence
 * @return the sum of the sequence
 */
unsigned long long sum_no_for(unsigned long long n)
{
        return ((3 * n) * (n + 1) / 2) - n; 
}
