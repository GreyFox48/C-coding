#include <stdio.h>

double calc_ang(double ang1, double ang2);
void print_ang(double ang3);

int main(void)
{
        double ang1;
        double ang2;
        double ang3;
        int cont = 1;

        while(cont == 1) {
                printf("Input the first angle of the triangle: ");
                scanf("%lf", &ang1);
                printf("Input the second angle of the triangle: ");
                scanf("%lf", &ang2);
                
                ang3 = calc_ang(ang1, ang2);
                
                print_ang(ang3);

                printf("Would you like to continue?\n1 for yes, 0 for no: ");
                scanf("%d", &cont);
        }

        return 0;
}

double calc_ang(double ang1, double ang2)
{
        return 180.0 - ang1 - ang2;
}

void print_ang(double ang3)
{
        printf("The missing angle is %.2lf.\n", ang3);
}
