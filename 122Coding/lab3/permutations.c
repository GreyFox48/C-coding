/**
 * @file permutations.c
 * @brief Test three different ways of creating an array of random elements.
 * @details Prints the average run times of three distinct random generation
 * over ten runs for different values.
 *
 * @author Matthew Olsen
 * @date March 5, 2016
 * @bug None
 * @todo None
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "randint.h"

int *lucky(size_t n);
int *used(size_t n);
int *knuth(size_t n);
void swap(int *a, int *b);
int nrandint(int range); 
void print_array(int a[], size_t n);
void seed(void); 
int nrandint(int range);
int *zero_array(int *a, size_t n);

#define ALLOC_FAILURE 300

int main(void)
{
        double sum = 0;
        size_t size;
        double start, stop;
        int *a = NULL;
        int i = 0;
        seed();
        
        /* lucky runs */
        puts("");
        printf("begin lucky run\n");
        size = 250;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = lucky(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                /* to prevent bug where malloc would allocate memory in same location, 
                 * creating an already populated array */
                a = zero_array(a, size); 
                free(a);
        }
        printf("avg for n = %zu for lucky is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 500;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = lucky(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for lucky is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 1000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = lucky(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for lucky is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 2000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = lucky(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for lucky is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        /* used runs */
        puts("");
        printf("begin used run\n");
        size = 2500;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 5000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 10000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 20000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 40000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;

        size = 80000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = used(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for used is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        /* knuth runs */
        puts("");
        printf("begin knuth run\n");
        size = 1000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 2000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 4000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 8000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 16000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 32000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        size = 64000;
        printf("run\tn\ttime\n");
        for (i = 0; i < 10; i++) {
                start = clock();
                a = knuth(size);
                stop = clock();
                printf("%d\t%zu\t%.4lf\n", i + 1, size, (double) (stop - start) / CLOCKS_PER_SEC);
                sum += (double) (stop - start) / CLOCKS_PER_SEC;
                a = zero_array(a, size);
                free(a);
        }
        printf("avg for n = %zu for knuth is %.4lf seconds\n", size, sum / 10);
        sum = 0;
        
        return 0;
}

/**
 * Generates an array of size n elements and places exactly one of the first
 * n integers in a random position in the array. Does so by generating a random
 * integer each time and testing to see if it is already in the array.
 * @param n the maximum integer to be given.
 * @return the array full the first n integers in a random order
 */
int *lucky(size_t n)
{
        int *a = NULL;
        int i, j, num;

        a = malloc(n * sizeof(int));
        if(!a){
                printf("Malloc failure in function lucky. Goodbye.\n");
                exit(ALLOC_FAILURE);
        }
        /* to initialize values in array a to prevent errors in below if*/
        a = zero_array(a, n); 

        for (j = 0; j < n; ) {
                num = nrandint(n);
                for (i = 0; i < n; i++) {
                        /* creates a failure case for next if statement */
                        if (a[i] == num) {
                                num = 0;
                                break;
                        }
                }
                /* if number was not detected */
                if (num != 0) {
                        a[j] = num;
                        j++;
                }                        
        }
        return a; 
} 

/**
 * Generates an array of size n elements and places exactly one of the first
 * n integers in a random position in the array. Does so by checking if a
 * generated number's index in a second array is set to 1.
 * @param n the maximum integer to be given.
 * @return the array full the first n integers in a random order
 */
int *used(size_t n)
{
        int *a = NULL;
        int *b = NULL;
        int i, num;

        a = malloc(n * sizeof(int));
        b = malloc(n * sizeof(int));
        /* to ensure below if doesnt call unitialized values in array b */
        b = zero_array(b, n); 
        if(!(a && b)){
                printf("Malloc failure in function lucky. Goodbye.\n");
                exit(ALLOC_FAILURE);
        }

        for (i = 0; i < n; ) {
                num = nrandint(n);
                /* -1 to composite for indexing */
                if (b[num - 1] == 1)
                        continue; /*failed so try again */
                a[i] = num;
                b[num - 1] = 1;
                i++;
        }

        free(b);
        return a; 
}
 
/**
 * Generates an array of size n elements and places exactly one of the first
 * n integers in a random position in the array. Does so by using knuth's 
 * algorithm.
 * @param n the maximum integer to be given.
 * @return the array full the first n integers in a random order
 */
int *knuth(size_t n)
{
        int *a = NULL;
        int i;

        a = malloc(n * sizeof(int));
        if(!a){
                printf("Malloc failure in function knuth. Goodbye.\n");
                exit(ALLOC_FAILURE);
        }

        for (i = 0; i < n; i++) {
                a[i] = i + 1;
        }

        for (i = 0; i < n; i++) {
                /* -1 to compensate to indexing */
                swap(&a[i], &a[nrandint(n) - 1]);
        }

        return a; 
}

/**
 * Swaps two given addresses with a bit wise swap.
 * @param a the first address to be swapped
 * @param b the second address to swapped
 * @return nothing
 */
void swap(int *a, int *b)
{
        if (*a != *b) {
                *a = *a ^ *b;
                *b = *b ^ *a;
                *a = *a ^ *b; 
        }
}

/**
 * Prints out the contents of an array.  For debugging purposes.
 * @param n the size of the array
 * @param a the array to be printed 
 * @return none
 */
void print_array(int a[], size_t n)
{
        int i;

        for (i = 0;i < n; i++) {
                printf("%d\n", a[i]);
        } 

}

/**
 * Zero out array because just freeing it doesn't seem to reset elements in
 * array (when next array is malloced, it will contain the old values still)
 * @param a the array to fill with zeros
 * @param n the size of the array
 * @return the zerod out array
 */
int *zero_array(int *a, size_t n)
{
        int i;
        
        for (i = 0; i < n; i++) {
                a[i] = 0;
        }
        return a;
}
