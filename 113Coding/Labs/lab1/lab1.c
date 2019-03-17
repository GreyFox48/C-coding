/**
 * @file lab1.c
 * @brief Calculates a few basic properties of a rectangle, circle, triangle, 
 * and regular polygon based on values of user input
 * @details Calculates the area, perimeter, and diagnol of a rectangle, the area 
 * and circumferance of a circle, the perimeter, area, and hypotenuse of a triangle,
 * and finally the exterior and interior angles of a regular polygon, along with 
 * its area.
 *
 * @author Matthew Olsen
 * @date September 5th, 2015
 * @bug User can input negative values.  Calculations utalizing pi are slightly off due to
 * rounding error.
 */

#include <stdio.h>
#include <math.h>

int area_rectangle(int rect_length, int rect_width);
int perimeter_rectangle(int rect_length, int rect_width);
double diagnol_rectangle(int rect_length, int rect_width);
double area_circle(double radius);
double circumference(double radius);
double perimeter_triangle(double tri_height, double tri_base);
double hypotenuse(double tri_height, double tri_base);
double area_triangle(double tri_height, double tri_base);
double exterior_angle(int side_number);
double interior_angle(int side_number);
double area_regular_polygon(int side_number, double side_length);

int main(void)
{
        int rect_length;
        int rect_width;
        int rect_perim;
        int rect_area;        
        double rect_diag;        
        double radius;
        double circum;
        double circ_area;
        double tri_height;
        double tri_base;
        double tri_perimeter;
        double tri_area;
        double tri_hyp;
        int side_number = 4;
        double side_length = 2;
        double ext_angle;
        double int_angle;
        double poly_area;
        
        printf("This program calculates basic propterties of rectangles, circles, triangles, and regular polygons. \n");        

        printf("Please input the width of your rectangle as a integer: ");
        scanf("%d", &rect_width);
        printf("Please input the length of your rectangle as a integer: ");
        scanf("%d", &rect_length);
        rect_perim = perimeter_rectangle(rect_length, rect_width);
        rect_area = area_rectangle(rect_length, rect_width);
        rect_diag = diagnol_rectangle(rect_length, rect_width);

        printf("The rectangle has a perimeter of %d, an area of %d and an diagnoal of length %lf.\n", rect_perim, rect_area, rect_diag);

        printf("Please input the radius of your circle: ");
        scanf("%lf", &radius);
        circum = circumference(radius);
        circ_area = area_circle(radius);               

        printf("The cicle has a circumferance of %lf and an area of %lf.\n", circum, circ_area);

        printf("Please input the base of your right triangle: ");
        scanf("%lf", &tri_base);
        printf("And now its height: ");
        scanf("%lf", &tri_height);         
        tri_perimeter = perimeter_triangle(tri_base, tri_height);
        tri_hyp = hypotenuse(tri_base, tri_height);
        tri_area = area_triangle(tri_base, tri_height);

        printf("The right triangle has a hypotenuse of %lf, an area of %lf, and a perimeter of %lf.\n", tri_hyp, tri_area, tri_perimeter);

        printf("Please input the number of sides on your regular polygon (integers only): ");
        scanf("%d", &side_number);  
        printf("And the lengths of the sides (only one side): ");
        scanf("%lf", &side_length);        
        ext_angle = exterior_angle(side_number);
        int_angle = interior_angle(side_number);
        poly_area = area_regular_polygon(side_number, side_length);
        
        printf("The regular polygon has an exterior angle of %lf degrees, and interior angle of %lf degrees, and an area of %lf.\n", ext_angle, int_angle, poly_area);         
        
        return 0;
}

/**
 *finds the area of a rectangle
 *@param rect_length the length of the rectanlge
 *@param rect_width  the width of the rectangle
 *@return the product of rect_length * rect_width
 */
int area_rectangle(int rect_length, int rect_width)
{
        return rect_length * rect_width;
}

/**
 *finds the area of a rectangle
 *@param rect_length the length of the rectanlge
 *@param rect_width  the width of the rectangle
 *@return the product of rect_length * 2 + rect_width * 2
 */
int perimeter_rectangle(int rect_length, int rect_width)
{
        return (rect_length * 2) + (rect_width * 2);
}

/**
 *finds the area of a rectangle
 *@param rect_length the length of the rectanlge
 *@param rect_width  the width of the rectangle
 *@return the product of sqrt(rect_length ^ 2 + rect_width ^ 2)
 */
double diagnol_rectangle(int rect_length, int rect_width)
{
        return sqrt(pow(rect_length, 2) + pow(rect_width, 2));
}

/**
 *finds the area of a circle
 *@param radius the radius of the circle
 *@return the product of pi * r^2
 */
double area_circle(double radius)
{
        return 3.141593 * pow(radius, 2);
}

/**
 *finds the circumference of a circle
 *@param radius the radius of the circle
 *@return the product of 2 * pi * radius
 */
double circumference(double radius)
{
        return 2 * 3.141593 * radius;
}

/**
 *finds the area of a triangle
 *@param tri_height the height of the triangle
 *@param tri_base the base of the triangle
 *@return the product of 0.5 * tri_height * tri_base
 */
double area_triangle(double tri_height, double tri_base)
{
        return 0.5 * tri_height * tri_base;
}

/**
 *finds the hypotenuse of a triangle
 *@param tri_height the height of the triangle
 *@param tri_base the base of the triangle
 *@return the product of sqrt(tri_height ^ 2 + tri_base ^ 2)
 */
double hypotenuse(double tri_height, double tri_base)
{
        return sqrt(pow(tri_height, 2) + pow(tri_base, 2));
}

/**
 *finds the perimeter of a triangle
 *@param tri_height the height of the triangle
 *@param tri_base the base of the triangle
 *@return the sum of tri_height, tri_base, and the calculated hypotenuse
 */
double perimeter_triangle(double tri_height, double tri_base)
{
        double hyp = sqrt(pow(tri_height, 2) + pow(tri_base, 2));      
        return hyp + tri_height + tri_base;
}

/**
 *finds the exterior angle of a regular polygon
 *@param side_number number of sides on the polygon
 *@return 360.0 / side_number
 */
double exterior_angle(int side_number)
{
        return 360.0 / side_number;
}

/**
 *finds the interior angle of a regular polygon
 *@param side_number number of sides on the polygon
 *@return 180.0 * (side_number - 2) / side_number
 */
double interior_angle(int side_number)
{
        return (180.0 * (side_number - 2)) / side_number;
}

/**
 *finds the exterior of a regular polygon
 *@param side_number number of sides on the polygon
 *@param side_length the length of a side of the polygon
 *@return ((side_length ^ 2) * side_number) / (4 * tan(pi / side_number)
 */
double area_regular_polygon(int side_number, double side_length)
{                
        return (pow(side_length, 2) * side_number) / (4 * tan(3.141593 / side_number));
}

