/**
 * @file newton_sqrt.c
 * @brief Determines the square root of numbers 1 to 100
 * @details Utilizes newton's method to help find the square root, and will
 * print the number of guesses to reach the proper percision
 *
 * @author Matthew Olsen
 * @date February 7, 2016
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <math.h>

/* helps optimize the newton_sqrt method */
#define START(x) ((x) >= (4) ? (x / 2) : (x))

double newton_sqrt(double num, double epsilon);

int main(int argc, char **argv)
{
        double sqrt = 0.0;
        int i = 0;
        int max = 100;
        /* desired percision is to the 9th decimal */
        double epsilon = 0.000000001;
        
        for (i = 1; i <= max; i++) {
                sqrt = newton_sqrt(i, epsilon);
                printf("%d|%3.9lf\n", i, sqrt);
        } 
        return 0;
}

/**
 * Searches for the square root of a given number through Newton's Method, and 
 * prints the number of guesses it took.
 * @param num the number to find the square root of
 * @param epsilon the desired degree of percision
 * @return the square root of num to the percision of epsilon
 */
double newton_sqrt(double num, double epsilon)
{
        /* Start begins guess at half if greater than 4 to help optimize */
        double sqrt = START(num);
        int loops = 0;
        
        /* fabs to ensure comparison is between positive numbers */
        while (fabs(sqrt * sqrt - num) >= epsilon) {
                /* Newton's method for the equation x^2 - num = 0 */
                sqrt = sqrt - (sqrt * sqrt - num) / (2 * sqrt);               
                loops++;
        }
        
        printf("%d|", loops);

        return sqrt;
}
