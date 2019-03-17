/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include "person.h"
#include <stdio.h>


void addEmployee(PERSON *employee) {
    printf("Please state the age of the employee: ");
    scanf("%d", &(employee->age));
    printf("Please state the height of the employee: ");
    scanf("%f", &(employee->height));
    printf("Please state the name of the employee: ");
    scanf("%s", employee->name); //include first and last or just first?
    printf("Please state the birthday of the employee (MM/DD/YYYY): ");
    scanf("%d/%d/%d", &(employee->bday.month), &(employee->bday.day), &(employee->bday.year));


}

void displayEmployee(PERSON *employee) {
    printf("Name: %s\n", employee->name);
    printf("Age: %d\n", employee->age);
    printf("Birth Date: %02d/%02d/%04d\n", employee->bday.month, employee->bday.day, employee->bday.year);
    printf("Height: %.2f meters", employee->height);
}

void displayAllEmployees(PERSON employees[], int numberOfEmployees) {
    int i = 0;

    for (i = 0; i < numberOfEmployees; i++) {
        displayEmployee(&(employees[i]));
        puts("\n"); /* just to make prettier */
    }
}

