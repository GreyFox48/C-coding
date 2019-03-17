/**
 * @file hexdump.c
 * @brief Mimicks the hexdump -C command
 * @details can only take one argument, and that is the file to be hexdumped.
 *
 * @author Matthew Olsen
 * @date February 27, 2018
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include "read_all.h"
#include <unistd.h>
#include "apue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void hexdump(int fd);

int main(int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__);
	}	

	hexdump(fd);
	close(fd);

	return 0;
}

/**
 * Prints the hexdump -C of the given file descriptor
 * @param fd the file descriptor of the file to be printed
 */
void hexdump (int fd) {
	int i, b_i;
	unsigned char *char_buff = malloc(sizeof(unsigned char) * 17);
	assert(char_buff);
	memset(char_buff, 0, 17);
	ssize_t bsize, nread;

	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "hexdump", __LINE__); 
	}
	unsigned char *buff = malloc(sizeof(unsigned char) * bsize);
	assert(buff != NULL);
	
	i = b_i = 0;
	while ((nread = read_all(fd, buff, bsize)) != 0) {
		for (b_i = 0 ; b_i < nread ; i++, b_i++) {
			if ((i % 16) == 0) {
				/* skip the first time */
				if (i !=0 ) {
					/*print what was printed */
					printf("  |%s|\n", char_buff);
				}
				/* print the offset for the current line */
				printf("%08x ", i);		
			}
			/* print the hexadecimal code */
			printf(" %02x", buff[b_i]);

			/* ensure position is a valid character */
			if ((buff[b_i] < 0x20) || (buff[b_i] > 0x7e)) {
		    		char_buff[i % 16] = '.';
			} else {
				char_buff[i % 16] = buff[b_i];
				char_buff[(i % 16) + 1] = '\0';
			}
		}		
	}

	b_i = i; /* lazy bit to save last offset */
	/* padding if line length less than 16 */
	for ( ;(i % 16) != 0; i++) {
		printf ("   ");
		char_buff[i % 16] = '\0';
	}
	char_buff[16] = '\0';

	printf("  |%s|\n", char_buff);
	printf("%08x\n", b_i);		

	free(char_buff);
	free(buff);
}
