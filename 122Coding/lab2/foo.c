#include <stdio.h>
#include <time.h>

unsigned long foo1(unsigned long n);
unsigned long foo2(unsigned long n);
unsigned long foo3(unsigned long n);
unsigned long foo4(unsigned long n);
unsigned long foo5(unsigned long n);
unsigned long foo6(unsigned long n);

/* #define PARTB */ /* for first test of all foo functions */
/* #define FOO1 */  /* test only foo1 function */
/* #define FOO2 */  /* and so on */
/* #define FOO3 */ 
/* #define FOO4 */ 
/* #define FOO5 */ 
 #define FOO6 

int main(void)
{
        unsigned long i, sum;
        clock_t start, stop; /* to time functions */
        
#ifdef PARTB
        /* time foo1 function */
        printf("foo1\n");
        for (i = 1; i <= 1000000000; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo1(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

        /* time foo2 function */ 
        printf("foo2\n");
        for (i = 1; i <= 100000; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo2(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

        /* time foo3 function*/
        printf("foo3\n");
        for (i = 1; i <= 1000; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo3(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

        /* time foo4 function*/ 
        printf("foo4\n");
        for (i = 1; i <= 100000; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo4(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

        /* time foo5 function*/
        printf("foo5\n");
        for (i = 1; i <= 100; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo5(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

        /* time foo6 function */ 
        printf("foo6\n");
        for (i = 1; i <= 100; i*=10) {
                start = clock(); /* to time function for each power of ten */
                sum = foo6(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }

#endif /* PARTB */

#ifdef FOO1
        /* time foo1 function */
        printf("foo1\n");
        for (i = 1000000000; i <= 10000000000; i+=1000000000) {
                start = clock(); /* to time function for each power of ten */
                sum = foo1(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO1 */

#ifdef FOO2
        /* time foo2 function */ 
        printf("foo2\n");
        for (i = 100000; i <= 1000000; i+= 100000) {
                start = clock(); /* to time function for each power of ten */
                sum = foo2(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO2 */

#ifdef FOO3
        /* time foo3 function*/
        printf("foo3\n");
        for (i = 1000; i <= 10000; i+=1000) {
                start = clock(); /* to time function for each power of ten */
                sum = foo3(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO3 */

#ifdef FOO4
        /* time foo4 function*/ 
        printf("foo4\n");
        for (i = 100000; i <= 1000000; i+= 100000) {
                start = clock(); /* to time function for each power of ten */
                sum = foo4(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO4 */

#ifdef FOO5
        /* time foo5 function*/
        printf("foo5\n");
        for (i = 100; i <= 1000; i+= 100) {
                start = clock(); /* to time function for each power of ten */
                sum = foo5(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO5 */

#ifdef FOO6
        /* time foo6 function */ 
        printf("foo6\n");
        for (i = 100; i <= 1000; i+= 100) {
                start = clock(); /* to time function for each power of ten */
                sum = foo6(i);
                stop = clock();
                printf("%lu|%lu|%lf\n", 
                  i, sum, (double) (stop - start) / CLOCKS_PER_SEC); 
        }
#endif /* FOO6 */

        return 0;
}

/**
 * Implements the first code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo1(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i;

        for (i = 0;i < n; i++) {
                sum++;
        }

        return sum;
}

/**
 * Implements the second code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo2(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i, j;

        for (i = 0;i < n; i++) {
                for (j = 0;j < n; j++) {
                        sum++;
                }
        }

        return sum;
}
        
/**
 * Implements the third code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo3(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i, j;

        for (i = 0;i < n; i++) {
                for (j = 0;j < n * n; j++) {
                        sum++;
                }
        }

        return sum;
}

/**
 * Implements the fourth code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo4(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i, j;

        for (i = 0;i < n; i++) {
                for (j = 0;j < i; j++) {
                        sum++;
                }
        }

        return sum;
}

/**
 * Implements the fifth code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo5(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i, j, k;

        for (i = 0;i < n; i++) {
                for (j = 0;j < i * i; j++) {
                        for (k = 0;k < j; k++) {
                                sum++;
                        }
                }
        }

        return sum;
}

/**
 * Implements the sixth code fragment from lab 2 
 * @param n the number of times the outer loop will be iterated
 * @return the calculated sum of the code fragment
 */
unsigned long foo6(unsigned long n)
{
        unsigned long sum = 0;
        unsigned long i, j, k;

        for (i = 1;i < n; i++) {
                for (j = 1;j < i * i; j++) {
                        if (j % i == 0) {
                                for (k = 0; k < j; k++) {
                                        sum++;
                                }
                        }
                }
        }

        return sum;
}
