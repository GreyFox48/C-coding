/**
 * @file lab4_q3.c
 * @brief Calculates the distance between 2 2-dimensional points uisng both the
 * manhattan forumula and the euclidean forumula
 *
 * @author Matthew Olsen
 * @date September 2015
 * @bug None
 * @todo Loop program until user decides to exit
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_LENGTH 25 /* to be used to define an array length later */

struct point2d_t
{
        double x;
        double y;
};

double get_euclidean(struct point2d_t point1, struct point2d_t point2);
double get_manhattan(struct point2d_t point1, struct point2d_t point2);

int main(void)
{
        struct point2d_t point1;
        struct point2d_t point2;
        double euclidean;
        double manhattan;
        char input[INPUT_LENGTH];

        printf("This program finds the euclidean and manhattan distance between two points.\n");

        /* user input for first data point */
        printf("Please input the x cooridinate of your first point.\n");
        fgets(input, INPUT_LENGTH - 1, stdin);
        point1.x = atof(input);

        printf("Please input the y cooridinate of your first point.\n");
        fgets(input, INPUT_LENGTH - 1, stdin);
        point1.y = atof(input);

        /* user input for second data point */
        printf("Please input the x cooridinate of your second point.\n");
        fgets(input, INPUT_LENGTH - 1, stdin);
        point2.x = atof(input);

        printf("Please input the y cooridinate of your second point.\n");
        fgets(input, INPUT_LENGTH - 1, stdin);
        point2.y = atof(input);

        euclidean = get_euclidean(point1, point2);
        manhattan = get_manhattan(point1, point2);


        printf("The Euclidean distance is %f, and the Manhattan distance is %f.\n", euclidean, manhattan);

        return 0;
}

/**
 * Finds the euclidean distance between points with an x and y coordinate
 * @param point1 the first point to be used in the euclidean formula
 * @param point2 the second point to be used in the euclidean formula
 * @return the euclidean distance between points point1 and point2
 */
double get_euclidean(struct point2d_t point1, struct point2d_t point2)
{
        /* euclidean distance forumula: ((x1-x2)^2 + (y1-y2)^2)^(1/2) */
        float xpoints = pow(point1.x - point2.x, 2.0);
        float ypoints = pow(point1.y - point2.y, 2.0);
        return sqrt(xpoints + ypoints);
}

/**
 * Finds the Manhattan distance between points with an x and y coordinate
 * @param point1 the first point to be used in the Manhattan formula
 * @param point2 the second point to be used in the Manhattan formula
 * @return the Manhattan distance between points point1 and point2
 */
double get_manhattan(struct point2d_t point1, struct point2d_t point2)
{
        /* manhattan distance forumula: abs(x1-x2) + abs(y1 - y2) */
        float xpoints = abs(point1.x - point2.x);
        float ypoints = abs(point1.y - point2.y);
        return xpoints + ypoints;
}
