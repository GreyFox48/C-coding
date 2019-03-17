/**
 * @file simpson.c * 
 * @brief Calculates the definite integrals of ln(x), e^x, sin(x), cos(x), and
 * sqrt(x) over an arbritary period.
 * @details Utilizes Simpon's Forumula to calculate integrals
 *
 * @author Matthew Olsen
 * @date May 27, 2016
 * @bugs None
 * @todo Nothing
 */

#include <math.h>
#include <stdio.h>

double simpsons(double (*f)(double), double a, double b);

int main(void)
{
        double a, b, area;

        /* integral of ln(x) */
        a = 0.5;
        b = 2.0;        
        area = simpsons(log, a, b);
        printf("integral of ln(x) from %lf to %lf is %lf\n", a, b, area);

        /* integral of e^x */
        a = 0.0;
        b = 1.0;        
        area = simpsons(exp, a, b);
        printf("integral of e^x from %lf to %lf is %lf\n", a, b, area);

        /* integral of cos(x) */
        a = 0.0;
        b = M_PI;        
        area = simpsons(cos, a, b);
        printf("integral of cos(x) from %lf to %lf is %lf\n", a, b, area);

        /* integral of sin(x) */
        a = 0.0;
        b = M_PI;        
        area = simpsons(sin, a, b);
        printf("integral of sin(x) from %lf to %lf is %lf\n", a, b, area);

        /* integral of x^(1/2) */
        a = 0.0;
        b = 10.0;        
        area = simpsons(sqrt, a, b);
        printf("integral of x^(1/2) from %lf to %lf is %lf\n", a, b, area);

        return 0;
}

/**
 * Calculates the definite integeral of a given function using Simpson's Rule.
 * @param f the pointer to the function to integrate
 * @param a the starting value of the definite integral
 * @param b the ending value of the definite integral
 * @return The calculated definite integral's value 
 */
double simpsons(double (*f)(double), double a, double b)
{
        double coefficent = (b-a)/6.0;
        double f_a = (*f)(a);
        double f_b = (*f)(b);
        double f_c = 4.0*(*f)((a+b)/2);
        return coefficent * (f_a + f_c + f_b);
}