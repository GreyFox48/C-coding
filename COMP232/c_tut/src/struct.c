/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>
#include "person.h"


int main(void) {
    int i, numberOfEmployees = 0;

    printf("Please enter the number of employees to be entered: ");
    scanf("%d", &numberOfEmployees);

    PERSON employees[numberOfEmployees];  //ASK ABOUT VERBAGE OF ADDEMPLOYEES, IF ARRAY SHOULD BE GLOBAL, ALLOCATED ARRAY

    puts("Begin entering employee data: ");
    for (i = 0; i < numberOfEmployees; i++) {
        puts("New employee.");
        addEmployee(&employees[i]);
        puts("");
    }
    puts("Finished entering employee data.");
    puts("Printing employee data: ");
    displayAllEmployees(employees, numberOfEmployees);

    return 0;
}
