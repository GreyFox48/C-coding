/**
 * @file fizzbuzz.c
 * @brief Fizzbuzz from 1 to 100
 * @details Fizz on multiples of 3, buzz for of 5, fizzbuzz for both 3 and 5
 *
 * @author Matthew Olsen
 * @date February 7, 2016
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>

int main(void)
{
        int i;
        
        for (i = 1; i <= 100; i++) {
                /* mults of 3 & 5 */
                if (i % 3 == 0 && i % 5 == 0){
                        printf("FizzBuzz\n");
                /* mults of 5 */
                } else if (i % 5 == 0) {
                        printf("Buzz\n");
                /* mults of 3 */
                } else if (i % 3 == 0) {
                        printf("Fizz\n");
                } else {
                /* just print the number */
                        printf("%d\n", i);
                }                
        }
        
        return 0;
}
