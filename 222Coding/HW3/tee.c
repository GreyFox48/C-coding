/**
 * @file tee.c
 * @brief mimicks the tee command, using default input and the -a option
 * 
 * @author Matthew Olsen
 * @date February 25, 2018
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

void tee_nfiles(int argc, char* argv[]);
void tee_append(int argc, char* argv[]);

int main(int argc, char* argv[])
{	
	int c;

	while ((c = getopt(argc, argv, "ah")) != -1) {
		switch (c) {
		case 'a':
			tee_append(argc, argv);
			return 0;
		case 'h':
			printf("tee replicates the tee command.\n");
			printf("\treads in file arguments to copy input from"
				" stdin to file and stdout.\n");
			printf("\t-a appends to the file(s).\n");
			printf("\t-h displays help.\n");
			return 0;
		case '?':
			printf("Please use -h for help.\n");
			return 1;
		}
	}

	tee_nfiles(argc, argv);

	return 0;
}

/**
 * creates new files, names based on the user input 
 * @param argc the number of arguments in argv
 * @param argv the character array of arguments
 */
void tee_nfiles(int argc, char* argv[])
{
	int i, bsize;
	ssize_t nread;
	/* - 1 to exlcude the program name */
	int files[argc - 1]; /* file descriptors */

	/* get the buffersize based on page size */
	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "tee_files", __LINE__); 
	}
	char buff[bsize];

	/* open the files */
	for (i = 0; i < (argc - 1); i++) {
		files[i] = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if (files[i] < 0) {
				err_sys("error in %s:%s:%d", __FILE__, 
				"tee_files", __LINE__);
		} 
	}

	/* read from stdin and put to stdout and the files */
	while((nread = read_all(0, buff, bsize)) != 0) {
		if (write(1, buff, nread) == -1) {
			err_sys("error in %s:%s:%d", __FILE__, "tee_files", __LINE__); 
		}
		for (i = 0; i < (argc - 1); i++) {
			if (write(files[i], buff, nread) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
				"tee_files", __LINE__); 
			}
		}
		
	}

	/* close the files */
	for (i = 0; i < (argc - 1); i++) {
		close(files[i]);
	}
	
}

/**
 * appends to files, names based on the user input 
 * @param argc the number of arguments in argv
 * @param argv the character array of arguments
 */
void tee_append(int argc, char* argv[])
{
	int i, bsize;
	ssize_t nread;
	/* -2 to exclude program name and -a option */
	int files[argc - 2]; /* file descriptors */

	/* get the buffersize based on page size */
	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "tee_files", __LINE__); 
	}
	char buff[bsize];

	/* open the files */
	for (i = 0; i < (argc - 2); i++) {
		files[i] = open(argv[i + 2], O_WRONLY | O_APPEND, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if (files[i] < 0) {
				err_sys("error in %s:%s:%d", __FILE__, 
				"tee_files", __LINE__);
		} 
	}

	/* read from stdin and put to stdout and the files */
	while((nread = read_all(0, buff, bsize)) != 0) {
		if (write(1, buff, nread) == -1) {
			err_sys("error in %s:%s:%d", __FILE__, "tee_files", __LINE__); 
		}
		for (i = 0; i < (argc - 2); i++) {
			if (write(files[i], buff, nread) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
				"tee_files", __LINE__); 
			}
		}
		
	}

	/* close the files */
	for (i = 0; i < (argc - 1); i++) {
		close(files[i]);
	}
	

}
