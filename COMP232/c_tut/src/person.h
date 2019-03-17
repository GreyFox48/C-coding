/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#ifndef PERSON_H_
#define PERSON_H_

typedef char NAME[256];

typedef struct date {
    int day;
    int month;
    int year;
} DATE;

typedef struct person {
    DATE bday;
    NAME name;
    int age;
    float height;
} PERSON;

void addEmployee(PERSON *employee);

void displayAllEmployees(PERSON employees[], int numberOfEmployees);

void displayEmployee(PERSON *employee);

#endif