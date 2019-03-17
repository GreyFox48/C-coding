/**
 * @file test_qsort.c
 * @brief Reads in a list of fruits from a file and sorts the list
 * @details the list must be newline seperated.  Sorts the list via qsort
 *
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

#define LEN 4096

enum{INIT = 1, GROW =2 };

struct fruits_t {
        int nval;
        int max;
        char **fruits;
};

void tolowercase(char *s);
void rstrip(char *s);
static int strcompare(const void *str1, const void *str2);

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
static int strcompare(const void *str1, const void *str2)
{
        /* To self: qsort will give function a pointer to a member of the array, 
           so with strings this means a pointer to a pointer */
        return strcmp(*(char **) str1, *(char **) str2);
}


int main(int argc, char *argv[])
{
        char buf[LEN];
        char *t = NULL;
        struct fruits_t fruits;
        fruits.max = INIT;
        fruits.nval = INIT;
        fruits.fruits = NULL;      

        int i;
        FILE *fp;

        fp = fopen(argv[1], "r");
        assert(fp);

        while(fgets(buf, LEN, fp)) {
                if (!fruits.fruits) {
                        fruits.fruits = malloc(sizeof(char *) * INIT);
                        assert(fruits.fruits);
                } else if (fruits.nval > fruits.max) {
                        fruits.fruits = realloc(fruits.fruits, GROW * fruits.max * sizeof(char *));
                        assert(fruits.fruits);
                        fruits.max *= GROW;
                }
                /* remove new line */
                rstrip(buf); 
                tolowercase(buf);
                t = malloc((strlen(buf) + 1) * sizeof(char));
                        assert(t);
                strncpy(t, buf, strlen(buf) + 1);
                fruits.fruits[fruits.nval - 1] = t; 
                fruits.nval++;
        }
        /* overcounted */
        fruits.nval--;
    
        /* print the list */
        for(i = 0; i < fruits.nval; i++) {
                printf("%s\n", fruits.fruits[i]);
        }

        printf("\n");

        qsort(fruits.fruits, fruits.nval, sizeof(char *), strcompare);

        /* print sorted list */ 
        for(i = 0; i < fruits.nval; i++) {
                printf("%s\n", fruits.fruits[i]);
        }
        
        /* you alloc it you clean it */
        fclose(fp);
        for (i = 0; i < fruits.nval; i++) {
                free(fruits.fruits[i]);
        }
        free(fruits.fruits);

        return 0;
}
