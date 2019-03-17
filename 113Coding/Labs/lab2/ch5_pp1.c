/**
 * @file ch5_pp1.c
 * @brief Determines the number of digits from input
 * 
 * @author Matthew C. Olsen
 * @date September 14, 2015
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20

int main(void)
{
        char s[ARRAY_SIZE];
        float input;
        int check_decimals;
        int digits;
        
        printf("Input a number: ");
        fgets(s, ARRAY_SIZE, stdin);
        input = atof(s);
        
        /* makes input postive if negative */
        if (input < 0) {
                input = -input;
        }

        /* if input contains decimals, removes them while preserving the number of integers via multipication by ten */
        while (((check_decimals = input) - input) < 0) { /* if truncated input - input is negative, input contains decimals */
                input = input * 10;
        }
 
        for (digits = 0; input >= 1; digits++) {
                input = input / 10.0;
        }     

        printf("The number has %d digits.\n", digits);
   
        return 0;
}
