#include <stdio.h>
#define LEN sizeof(d)/sizeof(int)

void swap(int d[], int i, int j)
{
	int temp;
	temp = d[i];
	d[i] = d[j];
	d[j] = temp;

	return;
}


void swap_array(int d[], int len)
{
	int i;

	for(i = 0; i < len/2; i++)
		swap(d,i,len-1-i);

	return;
}

void print_array(int d[], int len)
{
	int i;
	for(i = 0; i <= len; i++) 
		printf("%d ", d[i]);

	printf("\n");

	return;
}

int main()
{
	int d[] = {0,1,2,3,4,5,6};
	print_array(d,LEN);

	swap_array(d,LEN);
	print_array(d,LEN);

	return 0;

}
