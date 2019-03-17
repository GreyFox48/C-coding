/**
 * @file smallest.c
 * @brief Finds the LCM of a number from a given data range.
 * @ calculates utalizing prime number factorization
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None
 * @todo Ability to adjust number range based on user input
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX 20

void get_prime_factors(int *array, int number);
void compare_factors(int *factors, int *temp, size_t size);
int calculate_lcm(int *factors,size_t size);

int main(void)
{
        int rep = 0;
        int temp[MAX] = {0}; /* to temparily store prime factors of a given number */
        int pfactors[MAX] = {0}; /* holds all prime factors along with the largest power found in any number */
        size_t size = sizeof(temp) / sizeof(temp[0]);
        int ans;
        int i;  /* remove after debugging */

        /* start at index 1 for every number has a factor of 1 */
        for (rep = 1; rep < MAX; rep++){
                get_prime_factors(temp, rep);
                compare_factors(pfactors, temp, size);
                for(i = 0; i < MAX; i++){ /* resets temp for next number to factor */
                        temp[i] = 0;
                }
        }

        ans = calculate_lcm(pfactors, size);

        printf("The lcm of %d factorial is %d.\n", MAX, ans);

        return 0;
}
/**
 * computes the value and number of prime factors in a given number
 * and stores the number of prime factors in an array sequentially
 * @param primes the array to store the number of prime factors and
 * the respective values
 * @param number the number to calculate prime factors of
 */
void get_prime_factors(int *primes, int number){
        int rep;

        /* terminate at number / 2 because no number
         * will have factors greater than half of itself
         * excluding the number's identity
         */
        for (rep = 2; rep <= number / 2; rep++){
                if (number % rep == 0){
                        /* rep -1 adjusts for 0 indexing, for rep[1] for example should be the number of 2 factors and so on */
                        primes[rep - 1]++; /* first factor sequentially from 2 will always be a prime */
                        get_prime_factors(primes, number / rep);
                        return; /* prevents calculating wrong number of prime factors */
                }
        }

        primes[number - 1]++; /* if fails for loop test, number must be prime */
}

/**
 * compares two arrays, and if one array has a greater integer value
 * at a certain element than the other, assigns the value of the former
 * to the latter
 * @param factors the array to assign the larger value to
 * @param temp the array to compare factors to
 * @param size the length of temp and factors
 */
void compare_factors(int *factors, int *temp, size_t size){
        int rep;

        for (rep = 0; rep < size; rep++){
                if(factors[rep] < temp[rep]){
                        factors[rep] = temp[rep];
                }
        }
}

/**
 * calculates the product of an array of integers, assuming the first array index
 * represents the integer 1 and each element represents the power of each number
 * @param factors the list of factors in consecutive order with each element representing
 * their power
 * @param size the lenght of factors
 */
int calculate_lcm(int *factors, size_t size){
        int rep;
        int ans = 1; /* must be 1 to prevent product errors later */

        for (rep = 0; rep < size; rep++){
                if(factors[rep] > 0){
                        ans *= pow(rep + 1, factors[rep]);
                }
        }

        return ans;
}
