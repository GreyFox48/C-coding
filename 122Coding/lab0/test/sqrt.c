#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

/* binary search square root */
double sqrt_bin(double n, double epsilon)
{
        int num_guess = 0;
        double sq_rt = 0.0;
        double low = 0.0;
        double high = MAX(1.0, n);

        while (fabs(sq_rt * sq_rt - n) >= epsilon) {

                sq_rt = (low + high)/2.0;

                if (sq_rt * sq_rt > n) 
                        high = sq_rt;
                else
                        low = sq_rt;
                num_guess++;
        }
        
        printf("number of guesses to find the square root is %d\n", num_guess);

        return sq_rt;

}


int main(int argc, char **argv)
{
        if (argc != 2) {
                printf("usage: sqrt num\n");
                return 0;
        }
        
        double  n = strtod(argv[1], &argv[1]);
        double sq_rt = 0.0;
        
        clock_t start, end;
        start = clock();
        sq_rt = sqrt_bin(n, 0.000001);
        end = clock();

        printf("the square root of %f is %f\n", n, sq_rt);
        printf("And it took %3.24f seconds to calculate\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 0;
}

