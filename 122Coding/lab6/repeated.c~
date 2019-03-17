/**
 * @file repeated.c
 * @brief Finds the first repeated character from a string
 * @details None
 *
 * @date April 10, 2016
 * @author Matthew Olsen
 * @bugs none
 * @todo nothing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strchrrep(char *string);

int main(int argc, char **argv)
{
        char *temp = NULL;
        	
	if (argc != 2) {
		printf("error in input\n");
		printf("usage: ./repeated [STRING]\n");
		printf("where [STRING] is the string to find the first repeated character in\n");
		exit(EXIT_FAILURE);
	}

        temp = strchrrep(argv[1]);

        if(!temp) {
                printf("There are no repeat characters.\n");                
        } else {
                printf("first repeat character is: %c\n", *temp);
        }
        	
	return 0;
}

/**
 * Returns a pointer to the first repeated character in an string.  If no
 * repeats, returns NULL.
 * @param string the string to be scanned for repeats
 * @return NULL if no repeats, a pointer to the repeated character otherwise
 */ 
char *strchrrep(char *string) 
{
        int characters[128];
        int i;
        
        for (i = 0; i < strlen(string); i++) {
                characters[(int) *(string + i)]++;
                if (characters[(int) *(string + i)] > 1) {
                        return string + i;
                }
        }
        
        return NULL;
        
        
}
