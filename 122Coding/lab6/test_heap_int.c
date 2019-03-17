/**
 * @file test_qsort.c
 * @brief Reads in a list of ints from a file and sorts the list
 * @details the list must be newline seperated.  Sorts the list via a maxheap
 * implementation
 *
 * @author Matthew Olsen
 * @date April 10th, 2016
 * @bugs None
 * @todo Nothing
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "heapsort.h"

#define LEN 4096

enum{INIT = 1, GROW =2 };

struct heap_t {
        int nval;
        int max;
        int *elements;
};

void tolowercase(char *s);
void rstrip(char *s);
static int intcompare(const void *int1, const void *int2);

/**
 * Converts strings to lowercase strings
 * @param s the string to be converted
 */
void tolowercase(char *s)
{
        while (*s != '\0') {
                *s = tolower(*s);
                s++;
        }
}

/**
 * Trims off whitespace from the right of a string
 * @param s the string to be trimmed
 */
void rstrip(char *s)
{
        while (*s != '\0') {
                if (isspace(*s)) {
                        *s = '\0';
                        return;
                }
                s++;
        }
}

/**
 * Compares two string.  To be used explicitly for qsort in main
 * @param str1 the first string to be compared
 * @param str2 the second string to be compared
 * @return the difference between str1 and str 2
 */
static int intcompare(const void *int1, const void *int2)
{
        /* To self: qsort will give function a pointer to a member of the array, 
           so with strings this means a pointer to a pointer */
        return (*(int *) int1) - (*(int *) int2);
}

int main(int argc, char *argv[])
{
        char buf[LEN];
        struct heap_t heap;
        heap.max = INIT;
        heap.nval = INIT;
        heap.elements = NULL;      

        int i;
        FILE *fp;

        fp = fopen(argv[1], "r");
        assert(fp);

        while(fgets(buf, LEN, fp)) {
                if (!heap.elements) {
                        heap.elements = malloc(sizeof(int) * INIT);
                        assert(heap.elements);
                } else if (heap.nval > heap.max) {
                        heap.elements = realloc(heap.elements, GROW * heap.max * sizeof(int));
                        assert(heap.elements);
                        heap.max *= GROW;
                }
                /* remove new line */
                rstrip(buf); 
                tolowercase(buf);
                heap.elements[heap.nval - 1] = atoi(buf); 
                heap.nval++;
        }
        /* overcounted */
        heap.nval--;
    
        /* print the list */
	for(i = 0; i < heap.nval; i++) {
                printf("%d\n", heap.elements[i]);
        }
        printf("\n");

	/* todo sort list with heapsort */
	heapsort(heap.elements, heap.nval, sizeof(int), intcompare);
        /* user needs to provide comparison function */
	
        /* print the sorted list */
        for(i = 0; i < heap.nval; i++) {
                printf("%d\n", heap.elements[i]);
        }
        
        fclose(fp);        
        free(heap.elements);
 
       return 0; 
}
