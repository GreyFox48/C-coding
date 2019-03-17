/**
 * @file cube_binary.c
 * @brief Determines the cube root of numbers 1 to 100
 * @details utalizes binary search to search for the cube root, up to a
 * percision level of the 9th decimal place
 *
 * @author Matthew Olsen
 * @date February 7, 2016
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <math.h>

/* helps optimize the cube_binary method */
#define START(x) ((x) >= (6) ? (x / 3) : (x))

double cube_binary(double num, double epsilon);

int main(int argc, char **argv)
{
        double cube = 0.0;
        int i = 0;
        int max = 100;
        /* desired percision is to the 9th decimal */
        double epsilon = 0.000000001;
        
        for (i = 1; i <= max; i++) {
                cube = cube_binary(i, epsilon);
                /* output in end will be # loops|num|cube root of num */
                printf("%d|%3.9lf\n", i, cube);
        } 
        return 0;
}

/**
 * Searches for the cube root of a given number through binary search, and 
 * prints the number of guesses it took.
 * @param num the number to find the cube root of
 * @param epsilon the desired degree of percision
 * @return the cube roof of num to the percision of epsilon
 */
double cube_binary(double num, double epsilon)
{
        double cube = 0.0;
        /* If num >= 6 then reduces max to decrease total search field */ 
        double max = START(num);
        double min = 0.0;
        int loops = 0;
        
        /* fabs to ensure comparison is between positive numbers */
        while (fabs(cube * cube * cube - num) >= epsilon) {
                cube = (min + max) / 2;
                
                if (cube * cube * cube > num) {
                        max = cube;
                } else {
                        min = cube;
                }
                
                loops++;
        }
        
        printf("%d|", loops);

        return cube;
}
