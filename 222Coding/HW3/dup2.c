/**
 * @file dup2.c
 * @brief Mimicks the dup2() function
 * @details uses repeated use of dup() function to do so.
 *
 * @author Matthew Olsen
 * @date February 27, 2018
 * @todo Nothing
 * @bug none
 */

#include <unistd.h>
#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int dup_2(int oldfd, int newfd);

int main(int argc, char *argv[])
{
	int c, fd;

	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
		case '?':
			printf("Simple Interface to test the dup2.c code.\n");
			printf("./dup2 x y where x is the old fd and y is" 
				" to be the new fd.\n");
			return 0;
		}
	}

	if(argc != 3) {
		printf("use -h for help.\n");
	}
	fd = dup_2(atoi(argv[1]), atoi(argv[2]));

	close(fd);
	return 0;
}

/**
 * Mimicks the functionality of the dup2 function.
 * @param oldfd the fd to be copied to the new file descriptor
 * @param newfd the file descriptor to copy the old file descriptor to
 * @return -1 for failure from the program, else success.
 */
int dup_2(int oldfd, int newfd)
{
	int i, j;
	int files[newfd + 1]; /* +1 to possibly include the actual newfd value */
	/* strange case */
	if (oldfd == newfd) {
		return newfd;
	}
	/* free the new file descriptor in case it is in use */
	/* may or may not be open, so bad file desciptor error is ignored */
	if ((close(newfd) == -1) && (errno != EBADF)) {
		err_sys("error in %s:%s:%d", __FILE__, "dup_2", __LINE__); 
	}
	
	for(i = 0; ; i++) {
		if ((files[i] = dup(oldfd)) == -1) {
			err_sys("error in %s:%s:%d", __FILE__, "dup_2", __LINE__); 
		}
		/* got the proper fd number */
		if (files[i] == newfd) {
			break;
		/* somehow surpassed the newfd number */
		} else if (files[i] > newfd) {
			printf("Passed the newfd value in %s, %s\n",
				 __FILE__, "dup_2");
			return -1;
		}

	}

	/* close the unneeded file descriptors */
	for (j = 0; j < i; j++) {
		close(files[j]);
	}

	return files[i];	
}
