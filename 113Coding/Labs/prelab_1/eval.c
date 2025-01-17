#include <stdio.h>

double eval_frac(double input);
double eval_dec(double input);
void print_ans(double ans_frac, double ans_dec);

int main(void)
{
        double input;
        double ans_frac;
        double ans_dec;
        int cont = 1;
        
        printf("The function is (n / 3) + (2 / 3)\n");
        
        while(cont == 1) {
                printf("Please input n: ");
                scanf("%lf", &input);
        
                ans_frac = eval_frac(input);
                ans_dec = eval_dec(input);
        
                print_ans(ans_frac, ans_dec);  
                
                printf("Would you like to continue?\n1 for yes, 0 for no: ");
                scanf("%d", &cont);
        }      

        return 0;
}

double eval_frac(double input)
{
        return input + 2.0;
}

double eval_dec(double input)
{
        return ((input + 2.0) / 3.0);        
}

void print_ans(double ans_frac, double ans_dec)
{
        printf("The answer in fraction form is %lf / 3, and the decimal form is %lf. \n", ans_frac, ans_dec);
}

