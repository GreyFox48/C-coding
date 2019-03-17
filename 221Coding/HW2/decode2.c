#include <stdio.h>

long decode2(long x, long y, long z);

/*added b/c was uncertain if it was wanted or not */
int main(int arc, char **argv) {
	/* arbritrary values below */
	long x = 1, y = 2, z = 3, ans;

	ans = decode2(x, y, z);

	printf("Answer is %ld\n", ans);

	return 0;
}	

/*  Problem 3.58 is changed to c below */
long decode2(long x, long y, long z) {
	y = y - z;
	x = x * y;
	return x ^ ((y << 63) >> 63);
}
