/**
 * @file lab2.c
 * @brief Determines the smallest and the largest of four inputed integers.
 *
 * @author Matthew C. Olsen
 * @date September 14, 2015
 */

#include <stdio.h>

int main(void)
{
        int a;
        int b;
        int c;
        int d;
        int small1;
        int small2;
        int large1;
        int large2;

        printf("Please input four intergers: ");
        scanf("%d%d%d%d", &a, &b, &c, &d);
        
        /* determines smallest and largest of two pairs */        
        if (a <= b) {
                small1 = a;
                large1 = b;  
        } else {
                small1 = b;
                large1 = a; 
        }

        if (c <= d) {
                small2 = c;
                large2 = d;
        } else {
                small2 = d;
                large2 = c;
        }
        
        /* previous results are compared to each other and then printed */
        if (small1 <= small2) {
                printf("The smallest number is %d.\n", small1);
        } else {
                printf("The smallest number is %d.\n", small2);
        }

        if (large1 >= large2) {
                printf("The largest number is %d.\n", large1);
        } else {
                printf("The largest number is %d.\n", large2);
        }

        return 0;
}
