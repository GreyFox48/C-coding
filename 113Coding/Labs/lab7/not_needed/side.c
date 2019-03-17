#include <stdio.h>

int main(void)
{
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int *p = a;
	int *q = NULL;

	q = p++;  
	
	printf("a's address is %p\ta's value is %d\n", a, *a);
	printf("p's address is %p\tp's value is %d\n", p, *p);
	printf("q's address is %p\tq's value is %d\n\n", q, *q);

	q = ++p;
		
	printf("a's address is %p\ta's value is %d\n", a, *a);
	printf("p's address is %p\tp's value is %d\n", p, *p);
	printf("q's address is %p\tq's value is %d\n", q, *q);

	return 0;

}
