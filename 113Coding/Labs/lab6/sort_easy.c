#include <stdio.h>

void sort(int a[], int n)
{
	int cur, j, lowest_index, tmp;

	for(cur = 0; cur < n - 1; cur++) {
		/* each time through this loop scan the array
		 * from cur + 1 to end. If you find
		 * something lower than what is at cur, then
		 * swap it with current index. So each time
		 * through this loop, a[cur] will be
		 * properly sorted
		 *
		 * 1) first find the index of the lowest value
		 *
		 * if lowest_index remains unchanged, a[cur]
		 * is already sorted
		 */

		lowest_index = cur;
		for (j = cur + 1; j < n; j++) {

			/* if(a[j] < a[cur]) { */

			// corrected by Matthew Olsen 10/16/2015
			if(a[j] < a[lowest_index]){
				lowest_index = j;
			}
		}

		/* 2) now swap a[cur] and a[lowest_index]
		 * as long as a difference was found
		 */

		if (lowest_index != cur) {
			tmp = a[cur];
			a[cur] = a[lowest_index];
			a[lowest_index] = tmp;
		}
	} /* end for(cur = 0... */
}

void print_array(int a[], int n)
{
	int i = 0;

	for( ; i < n; i++)
		printf( i == n - 1 ? "%d\n" : "%d\t", a[i]);
}

int main(void)
{
	//int a[] = {5,2, 20,8};
	int a[] = {10,9, 8, 7, 6, 5, 4};
        //int a[] = {4, 2, 3, 4};
        size_t n = sizeof(a)/sizeof(a[0]);
	sort(a, (int) n);
	print_array(a, (int) n);

	return 0;
}
