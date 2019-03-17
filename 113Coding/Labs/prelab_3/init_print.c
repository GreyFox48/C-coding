/**
 * @file init_print.c
 * @brief prints the numbers 1 through 1000, one number per line, using a function
 *
 * @author Matthew Olsen
 * @date September 19th 2015 
 */

#include <stdio.h>

#define SIZE 1000

void print_array(int i[], size_t length);
 
int main(void)
{
        int i[SIZE];
        int count;
        
        for(count = 0; count < SIZE; count++) {
                i[count] = count + 1;
        }

        print_array(i, sizeof(i) / sizeof(i[0]));

        return 0;
}

/**
 * prints the contents of the array, one element per line
 * @param i[] the array to the printed
 * @param length the size of the array
 */
void print_array(int i[], size_t length)
{
        int count;        
        for(count = 0; count < length; count++) {
                printf("%d\n", i[count]);
        }
}
