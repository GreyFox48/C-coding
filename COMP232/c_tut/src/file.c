/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>

int main(void) {
    /* file handles */
    FILE *outputFile = NULL;
    FILE *inputFile = NULL;
    char buffer[256];
    char c;

    /* open files for writing*/
    inputFile = fopen("data.txt", "r");
    if (inputFile == NULL) {
        printf("data.txt could not be found.\n");
        return (1);    /* need to do explicit ERROR CHECKING */
    }

    printf("Input name of the output file: ");
    scanf("%s", buffer);
    outputFile = fopen(buffer, "w");

    while (EOF != (c = fgetc(inputFile))) {
        fputc(c, outputFile);
    }
    /* write some data into the file */

    /* don’t forget to close file handles */
    fclose(outputFile);
    fclose(inputFile);


    return 0;
}
