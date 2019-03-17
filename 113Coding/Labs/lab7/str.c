/**
 * @file str.c
 * @brief Implements various character array functions, such as removing
 * a specified character, finding the length, concatenating, copying, reversing
 * and swaping.
 * @details File contains redudent functions whose only difference is array
 * implementation versus pointer implementation.
 *
 * @author Matthew Olsen
 * @date 2015-10-28
 * @bug None
 * @todo None
 */

#include "str.h"
#include <stdio.h>

/**
 * determines the length of a string, not including the null terminator
 * @param s the string to find the length of
 * @return the length of the string
 */
/* accidently given by lab */
int str_len(char *s)
{
	/* this is here so code compiles */
        int len = 0;
        while (*s) {
                len++;
                s++;
        }
	return len;
}

/* array version */
/* concantenate t to the end of s; s must be big enough */
/* given by lab */
void str_cat(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0') 	/* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
		;
}

/* array version */
/* given by lab */
void squeeze(char s[], int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];

	s[j] = '\0';
}

/* given by lab */
void reverse(char *s)
{
	int c, i, j;

	for (i = 0, j = str_len(s) - 1; i < j; i++, j-- ) {
		/* change this so it calls cswap */
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}

}

/**
 * copies the elements of one string array into another for n characters
 * @param *dest the string to copy elements into
 * @param *src the string containing elements to be copied
 * @param n the amount of characters to be copied
 */
void pstr_ncpy(char *dest, char *src, int n)
{
        int i;
        for(i = 0; i < n && *(src + i); i++){
                *(dest + i) = *(src + i);
        }

        /* adds null characters for the rest of the specified length n */
        for ( ; i < n; i++){
                *(dest + i) = '\0';
        }
}

/**
  * concantenate t to the end of s; s must be big enough!  what to do in other case?
  * @param s the string append to
  * @param t the string to append to s
  */
void pstr_cat(char *s, char *t)
{
        char *i = s;
        char *j = t;
        while(*i)
                i++; /* find end of stirng s */
        while(*j){
                *i = *j;
                i++;
                j++;
        }

        *i = '\0'; /* \0 added later because while loop terminates at \0 */

}


/**
 * returns the difference between the character values of strings s and t
 * @param s string to be compared to t
 * @param t string to be compared to s
 * @param size number of characters to be compared, starting at beginning of string
 * @return the difference between the characters of s and t
 */
int pstr_ncmp(char *s, char *t, int size)
{
        int i = 0;
        int j = 0;
        for ( ; i < size; i++, j++){
                /* compares char values at each element */
                if(*(s + i) != *(t + j)){
                        return *(s + i) - *(t + j);
                }
        }

        return 0;
}

/**
 * finds the first address of a given char value in string s
 * @param s the character string to be searched
 * @param c the char value to be located
 * @return the address of the first occuring char value in s
 */
char *pindex(char *s, int c)
{
        int i = 0;

        do {
                if(*(s + i) == c){
                        return (s + i);
                }
                i++;
        } while(*(s + i - 1)); /* ensures loop will be able to search for
                                * possible null character */

        return NULL;
}

/**
 * removes any occurence of a character fron a given string
 * @param s the string to remove characters from
 * @param c the character to be removed
 */
void psqueeze(char *s, int c)
{
        int i;
        int j;
        for ( i = j = 0; *(s + i); i++){
                /* rearranges string by only adding characters that are not c */
                if (*(s + i) != c){
                        *(s + j) = *(s + i);
                        j++;
                }
        }

        *(s + j) = '\0'; /* null character needed for possibly new
                          * termination point */
}

/**
 * swaps two given characters
 * @param c the first character to be swapped
 * @param d the second character to be swapped
 */
void cswap(char *c, char *d)
{
        char temp = *c;
        *c = *d;
        *d = temp;
}

/**
 * reverses the order of the elements in a string
 * @param s the string to be reversed
 */
 void preverse(char *s)
 {
        int i;
        int len = str_len(s);

        for (i = 0; i < len / 2; i++){ /*swap everything till halfway point */
                cswap(s + i, s + (len - 1 - i));
                /* 1 hardcoded to prevent array out of bounds error */
        }
 }
