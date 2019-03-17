/**
 * @file init.c
 * @brief prints the numbers 1 through 1000, one number per line, using an array 
 *
 * @author Matthew Olsen
 * @date September 19th 2015 
 */

#include <stdio.h>

int main(void)
{
        int i[1000];
        int count;
        
        for(count = 0; count < 1000; count++) {
                i[count] = count + 1;
        }

        for (count = 0; count < 1000; count++) {
                printf("%d\n", i[count]);
        }

        return 0;
}
