#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "randint.h"

/**
 * returns a uniform random integer between 0 <= rand num <= range
 * @param range, defines the range of the random number [1,range]  
 * @return the generated random number
 */
int nrandint(int range) 
{
	return rand() % range + 1;
}

/**
 * call this to seed the random number generator rand()
 * uses a simple seed -- the number of seconds since the epoch 
 * call once before using nrandint and similiar functions that call rand()
 */
void seed(void) 
{
  	srand((unsigned int)time(NULL));
}
