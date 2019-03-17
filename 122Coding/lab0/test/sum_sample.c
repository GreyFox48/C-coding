#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long sum_forloop(unsigned long long n);

int main(int argc, char **argv) 
{
      if (argc != 2) {
            printf("usage: sum n\n");
            printf("find the sum of the first n integers\n");
            return 0;
      }  
      unsigned long long n = strtoull(argv[1], NULL, 10);
      unsigned long long sum = 0;
      
      clock_t start, end;
      start = clock();
      sum = sum_forloop(n);
      end = clock();

      printf("the sum from 1 to %llu is %llu\n", n, sum);
      printf("And it took %3.24lf seconds to calculate\n", (double) (end - start) / CLOCKS_PER_SEC);
      return 0;
}

unsigned long long sum_forloop(unsigned long long n)
{
      unsigned long long i = 1;
      unsigned long long sum = 0;
      
      for( ; i <= n; i++)
        sum += i;

      return sum;
}

