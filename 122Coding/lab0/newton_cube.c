/**
 * @file newton_cube.c
 * @brief Determines the cube root of numbers 1 to 100
 * @details Utilizes newton's method to help find the cube root, and will
 * print the number of guesses to reach the proper percision
 *
 * @author Matthew Olsen
 * @date February 7, 2016
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <math.h>

/* helps optimize the newton_cube method */
#define START(x) ((x) >= (6) ? (x / 3) : (x))

double newton_cube(double num, double epsilon);

int main(int argc, char **argv)
{
        double cube = 0.0;
        int i = 0;
        int max = 100;
        /* desired percision is to the 9th decimal */
        double epsilon = 0.000000001;
        
        for (i = 1; i <= max; i++) {
                cube = newton_cube(i, epsilon);
                printf("%d|%3.9lf\n", i, cube);
        } 
        return 0;
}

/**
 * Searches for the cube root of a given number through Newton's Method, and 
 * prints the number of guesses it took.
 * @param num the number to find the cube root of
 * @param epsilon the desired degree of percision
 * @return the cube root of num to the percision of epsilon
 */
double newton_cube(double num, double epsilon)
{
        /* Start begins guess at third of num if greater than 5 to optimize */
        double cube = START(num);
        int loops = 0;
        
        /* fabs to ensure comparison is between positive numbers */
        while (fabs(pow(cube, 3) - num) >= epsilon) {
                /* Newton's method for equation x^3 - num = 0 */
                cube = cube - (pow(cube, 3) - num) / (3 * pow(cube, 2));               
                loops++;
        }
        
        printf("%d|", loops);

        return cube;
}
