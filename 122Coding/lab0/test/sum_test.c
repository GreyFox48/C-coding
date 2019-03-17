#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long sum_for_loop(unsigned long long n);
unsigned long long sum_no_loop(unsigned long long n);

int main(int argc, char **argv) 
{
      if (argc != 2) {
            printf("usage: sum n\n");
            printf("find the sum of the first n integers\n");
            return 0;
      }  
      unsigned long long n = strtoull(argv[1], NULL, 10);
      unsigned long long sum1 = 0;
      unsigned long long sum2 = 0;      
      
      sum1 = sum_for_loop(n);
      sum2 = sum_no_loop(n);

      printf("sum1: %llu\n", sum1);
      printf("sum2: %llu\n", sum2);
      return 0;
}

unsigned long long sum_for_loop(unsigned long long n)
{
      unsigned long long sum = 0;
        unsigned long long i;

        for (i = 1; i <= n; i++) {
                /* sum of all numbers is last number plus next */
                sum = sum + (3 * i - 1);
        }

        return sum;
}

unsigned long long sum_no_loop(unsigned long long n)
{
        return ((3 * n) * (n + 1) / 2) - n; 
}
