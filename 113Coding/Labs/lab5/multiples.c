/**
 * @file multiples.c
 * @brief Finds sum of the multiples of 3 and 5 below certian number.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 * @todo Add user input to adjust range to find multiples
 */

#include <stdio.h>

int main(void)
{
        int ans = 0;
        int rep;

        for (rep = 0; rep < 1000; rep++){ /* start at 1 to not do modulo 0 */
                if (rep % 3 == 0 || rep % 5 == 0){ /* find multiples of three or five */
                        ans += rep;
                }
        }

        printf("The sum of all multiples of 3 or 5 below 1000 is %d.\n", ans);

        return 0;
}
