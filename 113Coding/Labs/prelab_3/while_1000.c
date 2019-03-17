/**
 * @file for_1000.c
 * @brief prints the numbers 1000 through 1, one number per line 
 *
 * @author Matthew Olsen
 * @date September 19th 2015 
 */

#include <stdio.h>

int main(void)
{
        int i;
        for(i = 1000; i >= 1; i--)
        {
                printf("%d\t", i);
        }

        return 0;
}
