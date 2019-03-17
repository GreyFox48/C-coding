/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>
#include <ctype.h>

#define DANGER_LEVEL 5    /* C Preprocessor -
			- substitution on appearance */

/* like Java ‘final’ */
int main(void) {
    char level;

    printf("Enter gas level: ");
    level = getc(stdin);
    level = tolower(level);
    /* if-then-else as in Java */

    switch (level) {
        case 'e':
            puts("Low on gas!");
            break;
        case 'h':
            puts("Half full!");
            break;
        case 'f':
            puts("Good driver!");
            break;
        default:
            puts("Shouldn't be here.");
    }



    /*
    if (level <= DANGER_LEVEL) /*replaced by 5
        printf("Low on gas!\n");
    else
        printf("Good driver !\n");

    return 0;
    */
}
