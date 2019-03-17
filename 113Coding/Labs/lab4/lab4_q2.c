/**
 * @file lab4_q2.c
 * @brief Enumerates colores to very arbritary numbers, and then prints them
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None 
 */

#include <stdio.h>

enum color
{
        RED = 18, ORANGE, YELLOW = 5, GREEN, BLUE, INDIGO = 14, VIOLET
};

int main(void)
{
        printf("RED is %d, ORANGE is %d, YELLOW is %d, GREEN is %d, BLUE is %d, INDIGO is %d, VOILET is %d.\n", RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET);
        return 0;
}
