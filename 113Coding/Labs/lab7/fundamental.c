/**
 * @file fundamental.c
 * @brief Prints data utalizing pointers.
 *
 * @author Matthew Olsen
 * @date 2015-10-28 
 */

#include <stdio.h>

int main (void)
{
        double p = 3.14159;
        double *a = NULL;

        a = &p;
        *a = 2.71828;

        printf("p's address is %p and the value is %lf\n", &p, p);
        printf("a's address is %p and the value is %p\n", &a, a);

        return 0;
}
