/**
 * @file dynamic.c
 * @brief Copies a couple a string literals into arrays and then manipulates.
 * @details Some functions are from custom implementations of standard c
 * fucntions.
 *
 * @author Matthew Olsen
 * @date 2015-10-28
 * @bug None
 * @todo None
 */

#include <stdio.h>
#include <stdlib.h>
/* #include <string.h> */
#include "str.h"

#define MALLOC_FAILED 1000

int main(void)
{
	char *s = "c run, c run unix, run unix run";

	char *t = ", go c, go!";

	char *u;

	size_t len = str_len(s) + str_len(t) + 1; /* 1 for the NULL char */

	/* how many objects times the size of the object */
	u = malloc(len * sizeof(char));

	/* malloc may fail so need to check to make sure it worked  */
	if (u == NULL) {
		printf("malloc failed. goodbye...\n");
		exit(MALLOC_FAILED);
	}

        /* the + 1 makes room for the null terminator */
	pstr_ncpy(u, s, str_len(s) + 1);
	printf("u = \"%s\"\n", u);

	pstr_cat(u, t);
	printf("u = \"%s\"\n", u);

	free(u);		/* you allocated it you free it */

	return 0;
}
