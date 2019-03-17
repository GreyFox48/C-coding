#include<stdio.h>


int main()
{
	int *p;
	int a, b;
	a = 0;
	b = 1;

	// corrected by Matthew Olsen 10/14/2015
	p = &a;
	/* p = a; */
	printf("%d\n", *p);

	// corrected by Matthew Olsen
	b = ++(*p);
	/* b = &p; */

	printf("%d\n", b);

 	return 0;
}
