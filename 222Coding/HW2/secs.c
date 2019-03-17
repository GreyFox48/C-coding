/**
 * @file secs.c
 * @brief File that prints the number of seconds since epoch.
 * @details Has a compile time definition to force an error.
 *
 * @author Matthew Olsen
 * @date February 15, 2018
 * @todo Nothing
 * @bug none
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define TIME_ERROR 1000

int main(int argc, char *argv[])
{
        time_t t;        

        #ifndef ERR_TEST
        if ((t = time(NULL)) == -1) {
                char msg[256];
                sprintf(msg, "error in %s:%s:%d", __FILE__ , "main", __LINE__);
                perror(msg);
                exit(TIME_ERROR);
        }       
        #endif

        #ifdef ERR_TEST
        if ((t = -1)) {
		errno = 14;
                char msg[256];
                sprintf(msg, "error in %s:%s:%d", __FILE__ , "main", __LINE__);
                perror(msg);
                exit(TIME_ERROR);
        }
        #endif

        printf("Number of second since the Epoch: %ld\n", t);

        return 0;

}
