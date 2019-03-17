#include <stdio.h>

int main(void)
{
        int *x = NULL;

        int y = 0;
        int z = 10;
	
	printf("x's address is %p\tx's value is NULL\n", x);
	printf("y's address is %p\ty's value is %d\n", &y, y);
	printf("z's address is %p\tz's value is %d\n\n", &z, z);

        x = &y;	
	printf("x's address is %p\tx's value is %d\n", x, *x);
	printf("y's address is %p\ty's value is %d\n", &y, y);
	printf("z's address is %p\tz's value is %d\n\n", &z, z);

	*x = 99;
	printf("x's address is %p\tx's value is %d\n", x, *x);
	printf("y's address is %p\ty's value is %d\n", &y, y);
	printf("z's address is %p\tz's value is %d\n\n", &z, z);
	
	x = &z;
	printf("x's address is %p\tx's value is %d\n", x, *x);
	printf("y's address is %p\ty's value is %d\n", &y, y);
	printf("z's address is %p\tz's value is %d\n\n", &z, z);

	*x = -101;
	printf("x's address is %p\tx's value is %d\n", x, *x);
	printf("y's address is %p\ty's value is %d\n", &y, y);
	printf("z's address is %p\tz's value is %d\n\n", &z, z);

        return 0;
}
