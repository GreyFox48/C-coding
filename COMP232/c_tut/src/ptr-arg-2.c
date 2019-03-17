/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>

void swap(char **, char **);

int main(void) {
    char *str1 = "five";
    char *str2 = "ten";

    printf("Before the swap: str1 = %s and str2 = %s\n", str1, str2);
    swap(&str1, &str2);
    printf("After the swap: str1 = %s and str2 = %s\n", str1, str2);

    return 0;
}

void swap(char **n1, char **n2) { /* passed and returned by using values of pointers */
    char *temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
