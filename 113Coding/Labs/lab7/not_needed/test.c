#include <stdio.h>
#include "str.h"
#include <stdlib.h>
#include <string.h>

/* #define STRLEN */
/* #define PSTRNCPY */
/* #define PSTRCAT */
 #define PSTRNCMP 
/* #define PINDEX */
/* #define PSQUEEZE */
/* #define PREVERSE */

/* ask about str_len already being given */
#define SIZE 100

int main(void)
{

	char s[] = "c run, c run unix, run unix run";

#ifdef STRLEN
	printf("the length of \"%s\" is %d\n", s, str_len(s));

#endif

#ifdef PSTRNCPY
	char s1[SIZE];

	/* copy s into s1 */
	pstr_ncpy(s1, s, str_len(s));
	printf("s1 = %s\n", s1);
#endif

#ifdef PSTRCAT
	char s1[SIZE];
	char *s2 = ", go c, go!";

	/* copy s into s1 */
	pstr_ncpy(s1, s, str_len(s));
	printf("s1 = %s\n", s1);
	pstr_cat(s1, s2);
	printf("s1 = %s\n", s1);
#endif

#ifdef PSTRNCMP
	char *t = "look c, look c";
	char *s2 = "look c, go c!";
	int min;
	int cmp;

	/* use the smallest length */
	min = str_len(s);
	if (str_len(t) < min)
		min = str_len(t);

	printf("comparing:\n");
	printf("%s\nand\n", s);
	printf("%s\n", t);
	if ((cmp = pstr_ncmp(s, t, min))) {
		printf("strings differ in the first %d chars; cmp = %d\n", min, cmp);
	} else
		printf("strings are the same for %d chars; cmp = %d\n", min, cmp);

	min = 8;
	printf("\ncomparing:\n");
	printf("%s\nand\n", t);
	printf("%s\n", s2);

	if ((cmp =pstr_ncmp(t, s2, min)))
		printf("strings differ in the first %d chars; cmp = %d\n", min, cmp);
	else
		printf("strings are the same for %d chars; cmp = %d\n", min, cmp);


	min++;

	printf("\ncomparing:\n");
	printf("%s\nand\n", t);
	printf("%s\n", s2);

	if ((cmp =pstr_ncmp(t, s2, min)))
		printf("strings differ in the first %d chars; cmp = %d\n", min, cmp);
	else
		printf("strings are the same for %d chars; cmp = %d\n", min, cmp);


#endif

#ifdef PINDEX

	printf("%s\n", s);
	char c = 'x';
	char *t = pindex(s, c);

	printf("searching for %c in \"%s\"\n", c, s);
	if (t != NULL)
		printf("%c is located at address %p\nwhich is %ld bytes from the base address %p\n", c, t, t - s, s);
	else
		printf("char %c not found in \"%s\"\n", c, s);

	c = 'a';
	t = pindex(s, c);
	printf("searching for %c in \"%s\"\n", c, s);
	if (t != NULL)
		printf("%c is located at address %p\nwhich is %ld bytes from the base address %p\n", c, t, t - s, s);
	else
		printf("char %c not found in \"%s\"\n", c, s);
#endif


#ifdef PSQUEEZE

	int c = 'r';
	printf("%s\n", s);
	psqueeze(s, c);
	printf("%s\n", s);
#endif

#ifdef PREVERSE

	printf("%s\n", s);
	printf("reversed is\n");
	preverse(s);
	printf("%s\n", s);
#endif

	return 0;

}
