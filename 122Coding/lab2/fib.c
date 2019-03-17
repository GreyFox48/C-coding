#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

unsigned max_n(void);
unsigned long *fib_array(unsigned n);
int check_n(unsigned n, unsigned *max_n);

#define NO_ARG 100
#define INVALID_ARG 101
#define ALLOC_FAILURE 102
#define INVALID_INPUT 103

int main(int argc, char *argv[])
{
        unsigned n; /* to be used to store user input */
        int c; /* to be used for getopt */       
        unsigned max_term = max_n() + 1;
        unsigned long *array = NULL;
        int i;

        if (argc != 3) {
                printf("Programs must take in one and only one argument.\n");
                printf("Please input -n x, where x is the Fibonacci term "
                        "to be calculated.\nGoodbye.\n");
                exit(NO_ARG);
        }
                
        while ((c = getopt(argc, argv, ":n:")) != -1) {
                switch (c) {
                case 'n':
                        n = (unsigned) atoi(optarg);
                        break;
                case ':':
                        printf("Invalid arguement. Only -n is valid.\n");
                        printf("Goodbye.\n");
                        exit(INVALID_ARG);
                        break;
                default:
                        printf("Error:  Switch statement in getopt fell through.\n");
                }
        } 

        /* ensure user input is not too big */     
        if (check_n(n, &max_term)) {
                printf("Please input a number less than or equal to 93 to "
                        "prevent overflow.\n");
                exit(INVALID_INPUT);
        }

        array = fib_array(n);

        /* +1 prevents off by one error */
        for (i = 0; i < n + 1; i++) {
                printf("%u|%lu\n", i, array[i]);
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
 * Checks to ensure user input is not too large for the program to calcualte.
 * @param n the user inputed Fibonacci term to calculate.
 * @param max_n the maximum n the program can calculate.
 * @return 0 is the program can calcualte the specified term or -1 if not
 */
int check_n(unsigned n, unsigned *max_n)
{
        if (n > *max_n)
                return -1;
        return 0;
}
