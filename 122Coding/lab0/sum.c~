/**
 * @file sum.c
 * @brief determines the sum of the sequence 2 + 5 + ... + (3n - 1), where n
 * is the number of integers in the sequence
 * @details utilizes a for loop to determine the sum
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

unsigned long long sum_loop(unsigned long long n);

int main(int argc, char **argv)
{
        unsigned long long num; /* the largest number in the sequence */
        unsigned long long sum = 0;
        int power = 0; /* to help increment num later */
        clock_t start, stop; /* to measure time it takes to process each num */

        for (power = 0; power < 10; power++) {
                num = pow(10, power);
                start = clock();
                sum = sum_loop(num);
                stop = clock();
                /* # of loops|size of n|total sum| time took */
                printf("%llu|%llu|%llu|%3.24lf\n"
                /* number of for loop tests equals num + 1 always */
                ,num  + 1, num, sum, (double) (stop - start) / CLOCKS_PER_SEC);
        }
        return 0;
}
/**
 * Determines the sum of the number sequence 2 + 5 + .. + (3n - 1), where n is
 * the number of intergers to sum.  Utilizes a for loop
 * @param n the number of intergers in the sequence
 * @return the sum of the sequence
 */
unsigned long long sum_loop(unsigned long long n)
{
        unsigned long long sum = 0;
        unsigned long long i;

        for (i = 1; i <= n; i++) {
                /* sum of all numbers in the sequence last number plus next */
                sum = sum + (3 * i - 1);
        }

        return sum;
}
