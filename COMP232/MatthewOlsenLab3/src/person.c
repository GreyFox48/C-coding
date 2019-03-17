/**
* Name: Matthew Olsen
* Lab: Lab 3 Personnel Records Application
* Date: 02/18/19
**/

#include "person.h"

LIST *head = NULL, *tail = NULL;

void inputPersonalData(PERSON *person) {
    // TODO Implement the function
    printf("Please input their name: ");
    scanf("%40s", person->name);
    printf("Please input their age: ");
    scanf("%d", &person->age);
    printf("Please input their height: ");
    scanf("%f", &person->height);
    printf("Please input their birthday in MM/DD/YYYY format: ");
    scanf("%d/%d/%d", &person->bday.month, &person->bday.day, &person->bday.year);

}

void addPersonalDataToDatabase(PERSON *person) {
    // TODO Implement the function
    add(&head, &tail, person);

}

void displayDatabase() {
    // TODO Implement the function
    for (LIST *node = head; node != NULL; node = node->next) {
        displayPerson(node->data);
        puts("");
    }
}

void displayPerson(PERSON *person) {
    // TODO Implement the function
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Height: %.2f\n", person->height);
    printf("%02d/%02d/%4d\n", person->bday.month, person->bday.day, person->bday.year);
}

PERSON *findPersonInDatabase(char *name) {
    // TODO Implement the function

    PERSON *currentPerson = NULL;
    for (LIST *node = head; node != NULL; node = node->next) {
        currentPerson = node->data;
        if (!(strcmp(name, currentPerson->name))) {
            return currentPerson;
        }
    }
    return NULL; // if not found
}

void removePersonFromDatabase(char *name) {
    // TODO Implement the function

    delete(&head, &tail, findPersonInDatabase(name));
}

void clearDatabase() {
    // TODO Implement the function
    clearRecursively(&head, &tail);

}
