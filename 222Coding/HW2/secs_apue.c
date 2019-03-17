#include "apue.h"
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
        time_t t;        

        #ifndef ERR_TEST
        if ((t = time(NULL)) == -1) {
                err_sys("error in %s:%s:%d", __FILE__ , "main", __LINE__); 
        }       
        #endif

        #ifdef ERR_TEST
        if ((t = -1)) {
		errno = 14;
                err_sys("error in %s:%s:%d", __FILE__ , "main", __LINE__); 
        }
        #endif

        printf("Number of second since the Epoch: %ld\n", t);

        return 0;

}
