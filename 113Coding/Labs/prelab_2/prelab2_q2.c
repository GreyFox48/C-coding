 /**
 * @file prelab2_q2.c
 * @brief outputs a witty pun based in user integer input
 *
 * @author Matthew Olsen
 * @date September 9, 2015
 * @bugs doesn't account for non-integer input
 */

#include <stdio.h>

int main(void)
{
        int input = 0;
        
        /* gets user user, with prompt */
        printf("Enter an integer: \n");
        scanf("%d", &input);

        /* says something witty if input is 1, 3, or 7.  Else gives a default response. */
        switch (input) {
        case 1:
                printf("One is the loneliest number. \n");
                break;
        case 3:
                printf("Three is just as bad as one. ");
                printf("But worse.  Because it's 3!\n");
                break;
        case 7:
                printf("And did you know seven ate nine?\n");
                break;
        default:
                printf("I can't sing about %d.\n", input);
        }

        return 0;
}
