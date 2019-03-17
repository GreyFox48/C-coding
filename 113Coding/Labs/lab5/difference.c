/**
 * @file difference.c
 * @brief Finds the difference between the square of the sums and the
 * sum of the squares of all natrual numbers up to 100.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 * @todo Ability to adjust number range based on user input
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int main(void)
{
        int i;
        int square_of_sums = 0;
        int sum_of_squares = 0;
        int nums[MAX];

        for(i = 0; i < MAX; i++){
                nums[i] = i + 1;
        }

        for(i = 0; i < MAX; i++){
                sum_of_squares += pow(nums[i], 2);
        }

        for(i = 0; i < MAX; i++){
                square_of_sums += nums[i];
        }
        square_of_sums = pow(square_of_sums, 2);

        printf("The difference is %d\n", square_of_sums - sum_of_squares);

        return 0;
}
