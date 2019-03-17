/**
 * @file prelab2_q1.c
 * @brief Says something witty, depending on user input of an integer
 *
 * @author Matthew Olsen
 * @date September 9, 2015
 * @bug Doesn't account for non-interger input
 */
#include <stdio.h>

int main(void)
{
        int input = 0;
        
        /* get user input, with prompt */
        printf("Enter an interger: \n");
        scanf("%d", &input);

        /* say something witty for numbers 1, 2, and 5, otherwise use a default response */
        if (input == 1) {
                printf("First is the worst.\n");
        } else if (input == 2) {
                printf("Second is the best. ");
                printf("Because it's the first prime! ");
        } else if (input == 5) {
                printf("But one could argue for five. ");
                printf("As it is the number of fingers on each hand.");
        } else {
                printf("I can't sing about %d.\n", input);
        }

        return 0;
}
