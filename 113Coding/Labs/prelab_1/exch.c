#include <stdio.h>

double dollars(double euro);
double euros(double dollar);
void print_exch(double dollar, double euro);

int main(void)
{
        double dollar;
        double euro;
        int cont = 1;
        int curr_type;

        printf("This program converts euros to dollars, or vise versa.\n");
        
        while(cont == 1) {
                printf("Enter 1 to convert US Dollars to Euros, or 0 to convert Euros to Dollars: ");
                scanf("%d", &curr_type);
                if(curr_type == 0) {
                        printf("Input the number of Euros to convert: ");
                        scanf("%lf", &euro);
                        dollar = dollars(euro);
                } else {
                        printf("Input the number of US Dollars to convert: ");
                        scanf("%lf", &dollar);
                        euro = euros(dollar);
                }
                
                print_exch(dollar, euro);

                printf("Would you like to continue?\n1 for yes, 0 for no: ");
                scanf("%d", &cont);
                 
        }

        return 0;
}

double dollars(double euro)
{
         return euro / 0.75;
}

double euros(double dollar)
{
        return dollar * 0.75;
}

void print_exch(double dollar, double euro)
{
printf("%.2lf US Dollars is worth %.2lf Euros.\n", dollar, euro);
}
