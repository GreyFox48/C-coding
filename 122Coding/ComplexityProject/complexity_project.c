/**
 * @file Complexity_Project
 * @brief interfaces with given functions
 * @details Times seven different functions five times each for a given n value
 *
 * @author Matthew Olsen
 * @date April 2, 2016
 * @bugs Program will segfault with large values of n for list functoins
 * @todo nothing
 */

#include "blackbox.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

unsigned long *create_list(unsigned long size);
void reverse_list(unsigned long *list, unsigned long size);
void randomize_list(unsigned long *list, unsigned long size);
unsigned long random_number(void);
void swap(unsigned long *x, unsigned long *y);
void print_list(unsigned long *list, unsigned long size);
void test_no_list(void (*f)(unsigned long), unsigned long n);
void test_with_list(void (*f)(unsigned long *, unsigned long), unsigned long *list, unsigned long n);

#define EXIT_HELP 100

int main(int argc, char *argv[])
{
        
        unsigned long size = 16;
        int function_number = 1;
        srandom(time(NULL)); /* needed for random number generator */
        int c;
        unsigned long *list = NULL;
        int i;
        
        while ((c = getopt(argc, argv, ":F:f:n:H")) != -1) {
                switch(c) {                
                case 'n':
                        size = atol(optarg);
                        break;
                case 'H':
                        printf("use -f to pick function.\n");
                        printf("use -n to pick f(n).\n");
                        exit(EXIT_HELP);
                        break;
                case 'f':
                        function_number = atoi(optarg);
                        break;
                }
        }

        //printf("size: %tu, f_n: %d\n", size, function_number);
        //unsigned long *list = NULL;
        //list = create_list(size);
        //print_list(list, size);
        //free(list);

        /* case number based on function number being chosen */
        switch(function_number) {
        case 1:
                for (i = 0; i < 5; i++)
                        test_no_list(function_1, size);
                break;
        case 2:
                for (i = 0; i < 5; i++)
                        test_no_list(function_2, size);
                break;
        case 3:
                printf("Sorted Ascending List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        test_with_list(function_3, list, size);
                        free(list);
                }
                printf("Sorted Descending List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        reverse_list(list, size);
                        test_with_list(function_3, list, size);
                        free(list);                
                }
                printf("Randomized List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        randomize_list(list, size);
                        test_with_list(function_3, list, size);
                        free(list);                
                }
                break;
        case 4:
                for (i = 0; i < 5; i++)
                        test_no_list(function_4, size);
                break;
        case 5:
                for (i = 0; i < 5; i++)
                        test_no_list(function_5, size);
                break;
        case 6:
                printf("Sorted Ascending List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        test_with_list(function_6, list, size);
                        free(list);      
                }
                printf("Sorted Descending List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        reverse_list(list, size);
                        test_with_list(function_6, list, size);
                        free(list);      
                }
                printf("Randomized List:\n");
                for (i = 0; i < 5; i++) {
                        list = create_list(size);
                        randomize_list(list, size);
                        test_with_list(function_6, list, size);
                        free(list);      
                }     
                break;
        case 7:
                for (i = 0; i < 5; i++)
                        test_no_list(function_7, size);
                break;
        }

        return 0;
}

/**
 * Creates a list of size n elements, sorted from [0, n-1]
 * @param n the number of elements to be in the list
 * @return the sorted list of size n
 */
unsigned long *create_list(unsigned long size)
{
        unsigned long *list = NULL;
        int i;

        list = malloc(size * sizeof(unsigned long));
        assert(list);
        for (i = 0; i < size; i++) {
                *(list + i) = i;
        }

        return list;
}

/** 
 * Reverses the order of a given list
 * @param list the list to be reversed
 * @param size the number of elements in list
 */
void reverse_list(unsigned long *list, unsigned long size)
{
        unsigned long i;
        for (i = 0; i < (size / 2); i++) {
                /* -1 to prevent out of bounds error */
                swap(list + i, list + (size - 1) - i);
        }
}
/**
 * Randomizes a given list of size up to 2^64-1 elements.  Takne from pdf.
 * @param list the list of elements to be sorted
 * @param size the number of elements in the list
 */
void randomize_list(unsigned long *list, unsigned long size)
{
        unsigned long i, j;
        for(i = size - 1; i > 0; i--) {
                j = random_number() % (i + 1);
                swap(list + i, list + j);
        }
}

/**
 * Creates a pseudo-random unsigned long between 0 and 2^64-1.  Taken from pdf.
 */
unsigned long random_number(void)
{
        unsigned long n, p, r;
        int i;

        n = 0;
        for (i = 0, p = 1; i < 8; i++, p*= 256) {
                /* generates a random 8 bits */
                r = random() % 256;
                n += r * p;
        }
        return n;        
}

/**
 * Swaps two elements using a bitwise swap
 * @param x the first element to be swaped
 * @param y the second element to be swapped
 */
void swap(unsigned long *x, unsigned long *y)
{
        /* prevent changing both values to zero */
        if (*x == *y)
                return;
        *x = *x ^ *y;
        *y = *y ^ *x;
        *x = *x ^ *y;
}

/**
 * Prints the contents of the list, for testing purposes.
 * @param list the list to print
 * @param size the number of elements in the list
 */
void print_list(unsigned long *list, unsigned long size)
{
        unsigned long i;
        for (i = 0; i < size; i++) {
                printf("Element %lu: %lu\n", i, list[i]);
        }
}

/**
 * Times a function to complete for a given n.  Prints n and time.
 * @param f the function to be tested
 * @param n the value to test f with
 */
void test_no_list(void (*f)(unsigned long), unsigned long n)
{
        clock_t time_elapsed;
        int msec;

        time_elapsed = clock();

        (*f)(n);

        time_elapsed = clock() - time_elapsed;
        msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

        printf("%lu %d.%03d\n", n, msec/1000, msec%1000);
}

/**
 * Times a function that contains a list.  Prints n and time function took.
 * @param f the function to be timed that that takes a unsigned long list 
 * and an unsigned long
 * that is the size of said list
 * @param list the list to be passed to function f
 * @param n the number of elements in list
 */ 
void test_with_list(void (*f)(unsigned long *, unsigned long), unsigned long *list, unsigned long n)
{
        clock_t time_elapsed;
        int msec;

        time_elapsed = clock();

        (*f)(list, n);

        time_elapsed = clock() - time_elapsed;
        msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

        printf("%lu %d.%03d\n", n, msec/1000, msec%1000);
}
