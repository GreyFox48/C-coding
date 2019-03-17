#include <stdio.h>
#include <stdlib.h>


#define MALLOC_FAILED -99
#define LEN 100

int main(void)
{
	int size;
	double *d;
	char buf[LEN];
	int i = 0;


	printf("Enter a size for your array: ");
	
	fgets(buf, LEN, stdin);
	sscanf(buf, "%d", &size);
	
	d = malloc(size * sizeof(double));
	
	if (d == NULL) {
		printf("malloc failed. goodbye...\n");
		exit(MALLOC_FAILED);
	}
		
	/* initialize elements to zero */
	for (i = 0; i < size; i++)
		*(d + i) = 0.0;

	i = 0; 			/* reset i */

	while (i < size) {

		printf("Enter a value: ");

		/* Ctrl+d pressed or some other error, fgets returns NULL*/
		if (fgets(buf, LEN, stdin) == NULL) {
			printf("\n");
			break;
		}

		sscanf(buf, "%lf", &d[i++]);
	}
	

	for (i = 0; i < size; ++i)
		printf("%lf\n", *(d + i));

	return 0;

}
