/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>
#include <arpa/nameser.h>

int main(void) {
    int nStudents = 0; /* Initialization, required */
    int nFaculty = 0;

    printf("How many students does CSUCI have ?:");
    scanf("%d", &nStudents);  /* Read input */
    //printf("CSUCI has %d students.\n", nStudents);
    printf("How many faculty does CSUCI have ?:");
    scanf("%d", &nFaculty);  /* Read input */
    //printf("CSUCI has %d faculty.\n", nStudents);
    printf("The ratio of student to faculty is %lf.\n", (float) nStudents / nFaculty);
    return 0;
}
