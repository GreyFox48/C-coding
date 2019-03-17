/**
 * @file zeros.c
 * @brief writes a file full of zeros to the file named zerosx
 * @details writes to zerox, where x is the specified lenght by -n.
 *
 * @author Matthew Olsen
 * @date February 27, 2018
 * @todo Nothing
 * @bug none
 */

#include "read_all.h"
#include <unistd.h>
#include <stdio.h>
#include "apue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int fd, c;
	ssize_t written, bsize;
	char name[64];

	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}
	char *buff = malloc(sizeof(char) * bsize);
	assert(buff != NULL);

	
	while ((c = getopt(argc, argv, "n:h")) != -1) {
		switch (c) {
		case 'h':
			printf("Creates a file, filled with zeros, based on the"
				" user specified length.\n");
			printf("The file name will be zerosx, where x is the"
				" number specified by n.\n");
			printf("\t-n specifies the number of zero bytes to fill.\n");
			printf("\t-h displays the help function.\n");
			return 0;
		case 'n':
			written = (ssize_t) atol(optarg);
			break;
		case '?':
			printf("Use -h for help.\n");
			return 0;
		}
	}

	/* create the name string */
	sprintf(name, "zeros%ld", written);
	/* create the buffer full of zeros */
	memset(buff, 0, bsize);

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fd < 0) {
			err_sys("error in %s:%s:%d", __FILE__, 
			"main", __LINE__);
	} 

	while(written > 0) {	
		/* if the remaining bytes to be written less than pagesize */	
		if ( written < bsize ) {
			bsize = written;
		}
		if (write(fd, buff, bsize) == -1) {
			err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
		}
		written -= bsize;		
	}


	close(fd);
	free(buff);

	return 0;
}
