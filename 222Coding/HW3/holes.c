/**
 * @file holes.c
 * @brief Writes numbers in a file hole
 * @details Write 1 at byte position 1, 3 at 1,000, 5 at 100,000, and 6 at
 * 1,000,000.
 *
 * @author Matthew Olsen
 * @date February 25, 2018
 * @todo Nothing
 * @bug none
 * ls -l fire_in_the_hole: 
 * -rw-r----- 1 suspiciousfox suspiciousfox 1000001 Feb 25 20:24 fire_in_the_hole
 * du fire_in_the_hole:
 * 16	fire_in_the_hole
 */

#include "read_all.h"
#include <unistd.h>
#include <stdio.h>
#include "apue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd;	

	fd = open("fire_in_the_hole", O_WRONLY | O_TRUNC | O_CREAT, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fd < 0) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (lseek(fd, 1, SEEK_SET) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (write(fd, "1", 1) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (lseek(fd, 1000, SEEK_SET) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (write(fd, "3", 1) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (lseek(fd, 100000, SEEK_SET) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (write(fd, "5", 1) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (lseek(fd, 1000000, SEEK_SET) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	if (write(fd, "6", 1) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}

	close(fd);

	return 0;
}
