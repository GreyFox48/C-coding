#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned max_n(void);
double fib(unsigned n);
unsigned long *fib_array(unsigned n);
double calc_error(unsigned long true, unsigned long measured);

/* the starting size of the array of Fibonacci terms */
#define START 16
#define ALLOC_FAILURE 100

int main(void)
{
        unsigned long *array = NULL;
        /* the max term is one too large */
        unsigned max_term = max_n() + 1;
        unsigned i;

        array = fib_array(max_term);

        /* +1 prevents off by one error */
        for (i = 0; i < max_term + 1; i++) {
                printf("f[%u] = %lu\n", i, array[i]);
        }

        for (i = 0; i < max_term + 1; i++) {
                if (array[i] != (unsigned long) fib(i - 1) && i != 0) {
                        puts("");
                        printf("error in %u term of forumula Fibonacci\n", i);
                        printf("terms differ by %lu\n", 
                          (unsigned long) fib(i - 1) - array[i]);
                        printf("percentage error %.18lf%% \n", 
                          calc_error(array[i], (unsigned long) fib(i - 1)));
                }
        }
        free(array);

        return 0;
}

/**
 * Calculates the largest unsigned long the computer can calculate by finding n
 * from the equation ULONG_MAX=(1/5^.5)((1+5^.5)/2)^(n+1).
 * @return the largest Fibonacci number the computer can calculate using
 * unsigned longs.
 */
unsigned max_n(void)
{
        double numerator = log(ULONG_MAX * sqrt(5));
        double denominator = log((1 + sqrt(5)) / 2);
        return (unsigned) floor((numerator / denominator) - 1);
}

/**
 * Calculates the nth Fibonacci term, from the equation Fn=1/(5^.5) *
 * (((1 + 5^.5)/2)^(n + 1) - ((1 - 5^.5)/2)^(n + 1)) 
 * @param n the number of the Fibonacci term to be calculated
 * @return the nth Fibonacci term
 */
double fib(unsigned n)
{
        double first_term = pow(((1 + sqrt(5)) / 2), n + 1);
        double second_term = pow(((1 - sqrt(5)) / 2), n + 1);
        return (1 / sqrt(5)) * (first_term - second_term); 
}

/**
 * Calculates an array of unsinged long Fibonacci terms, by adding the two 
 * previous terms together.
 * @param n the number of Fibonacci terms to be calculated
 * @return the pointer to a size n array of unsigned long consecqutive
 * Fibonacci numbers.
 */
unsigned long *fib_array(unsigned n)
{
        /* +1 prevents off by one error */
        unsigned long *array = malloc((n + 1) * sizeof(unsigned long));
        int i;

        if (!array) {
                printf("Malloc failed in fib_array.  Goodbye!\n");
                exit(ALLOC_FAILURE);
        }

        /* needed to start the array */
        array[0] = 0;
        array[1] = 1;

        /* Calcs technically begin at second term */
        for(i = 2; i < n + 1; i++) {
                array[i] = array[i - 1] + array[i - 2];
        }

        return array;
}

/** 
 * Calculates the difference between two unsigned long integers
 * @param true the true value
 * @param measured the measured value
 * @return the percentage difference between two measured values
 */
double calc_error(unsigned long true, unsigned long measured)
{
        /* doubles are to ensure decimals are being factored into calculation */ 
        return (double) (measured - true) / true * 100.0;
} 
