/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>

#define MAX_NUM_OF_CELLS 128

int main(void) {
    double number[MAX_NUM_OF_CELLS];
    double sum = 0;
    int i, cells = 0;

    puts("Provide a max number of doubles?");
    scanf("%d", &cells);

    if (cells > MAX_NUM_OF_CELLS) {
        printf("Beyond accepted number of cells.  Cells set to %d.", MAX_NUM_OF_CELLS);
        cells = MAX_NUM_OF_CELLS;
    }

    puts("Provide the number of doubles?");
    for (i = 0; i < cells; i++) {
        scanf("%lf", &number[i]);
        //printf("%lf", number[i]); /*for debugging*/
    }

    printf("Data:");
    for (i = 0; i < cells; i++) {
        sum += number[i];
        printf(" %lf", number[i]);
    }
    puts("");

    printf("Average: %lf", (float) sum / cells);


    /*
    for (int index = 0; index < MAX_NUM_OF_CELLS; index++) {
        number[index] = index;
    }
    */
    /* now, number[index]=index; will cause error: why ?*/
    /*
    for (int index = 0; index < MAX_NUM_OF_CELLS; index = index + 1) {
        sum += number[index];  /* sum array elements */
    //}
    /*
    printf("sum = %d\n", sum);
    */

    return 0;
}
