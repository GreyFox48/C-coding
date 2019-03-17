#include <stdio.h>

double add(double, double);

double sub(double, double);

double mult(double, double);

double div(double, double);
/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

double calc(double (*f)(double, double), double, double);

int main(void) {
    double a, b, ans = 0;
    char opp;
    printf("calc>");
    scanf("%lf %s %lf", &a, &opp, &b);
    switch (opp) {
        case '+':
            ans = calc(add, a, b);
            break;
        case '-':
            ans = calc(sub, a, b);
            break;
        case '*':
            ans = calc(mult, a, b);
            break;
        case '/':
            ans = calc(div, a, b);
            break;
    }
    printf("%lf\ncalc>\n", ans);

    return 0;
}

double calc(double (*f)(double, double), double a, double b) {
    return (*f)(a, b);    /* call function *f with param */
}

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mult(double a, double b) {
    return a * b;
}

double div(double a, double b) {
    return a / b;
}
