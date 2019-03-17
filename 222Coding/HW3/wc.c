/**
 * @file wc.c
 * @brief Mimicks the wc command
 * @details impliments the -c, -l, and -w commands.  Can read from stdin and 
 * from a file.
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
#include <ctype.h>
#include <string.h>

void counter(int argc, char* argv[]);
void getcount(char buff[], ssize_t size);

unsigned long char_count;
unsigned long word_count;
unsigned long line_count;
char on_word;

int main (int argc, char *argv[])
{
	int i,c,w,l;
	ssize_t bsize;
	c = w = l = 0;

	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}
	char buff[bsize];

	while ((i = getopt(argc, argv, "cwlh")) != -1) {
		switch (i) {
		case 'c':
			c = 1;
			break;
		case 'w':
			w = 1;
			break;
		case 'l':
			l = 1;
			break;
		case 'h':
			snprintf(buff, bsize, "mimicks the functionality of wc.\n");
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}
			snprintf(buff, bsize, "\t-c number of bytes in the file.\n");
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}	
			snprintf(buff, bsize, "\t-w number of words in the file.\n");
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}	
			snprintf(buff, bsize, "\t-l number of lines in the file.\n");
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}	
			snprintf(buff, bsize, "can either read one file for from stdout.\n");
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}
			return 0;
			
		}

		
	}

	counter(argc, argv);

	if (l == 1) {
		snprintf(buff, bsize, " %ld ", line_count);
		if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
		}
	}
	if (w == 1) {
		snprintf(buff, bsize, " %ld ", word_count);
		if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
		}
	}
	if (c == 1) {
		snprintf(buff, bsize, " %ld ", char_count);
		if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
		}
	}
	if ((l == 0) && (w == 0 && (c == 0))) {
		snprintf(buff, bsize, " %ld %ld %ld", line_count, word_count, char_count);
		if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
		}
	}

	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '-') == NULL) {
			snprintf(buff, bsize, " %s ", argv[i]);
			if (write(1, buff, strlen(buff)) == -1) {
				err_sys("error in %s:%s:%d", __FILE__, 
					"main", __LINE__); 
			}
		}
	}


	return 0;
	
}

/**
 * Counts the content so the buffer.
 * @param buff the buffer to read from.
 * @param size the size of the contents of the buffer.
 */
void getcount(char buff[], ssize_t size)
{
	ssize_t i = 0;

	/* counts for edge case of last buffer ending on end of word */
	if(isspace(buff[i])) {
		on_word = 0;
	}

	while (i < size) {
		/* find the beginning of the word, 
		 * count and line characters till then*/
		for ( ; i < size; i++) {
			/* detect word */
			if (!isspace(buff[i])) {
				/* if was not on word before, now on word */
				if (on_word == 0) {
					on_word = 1;
					word_count++;
					break;
				}
				/*resume from split word, don't count */
				break;
			}

			char_count++;        
			if ((buff[i]) == '\n') { 
				line_count++;
			}
		}

		/* count characters till the end of the word */
		for ( ; i < size; i++) {
			char_count++;
			if ((buff[i]) == '\n') { 
				line_count++;
			}			
			/* reached the end of the word, so no more counting */
			if (isspace(buff[i])) {
				on_word = 0; /* no longer on word */
				i++; /* move counter */
				break;
			}
		}
	}

}
           
/**
 * breaks the input into managable buffers for the function to read over
 * @param argc the argument count
 * @param argv the argument list
 */
void counter(int argc, char* argv[])
{
	int fd = 0; 
	int bsize, i;
	ssize_t nread;

	for (i = 1; i < argc; i++) {
		if (strchr(argv[i], '-') == NULL) {
			fd = open(argv[i], O_RDONLY);
			if (fd < 0) {
				err_sys("error in %s:%s:%d", __FILE__, "counter", __LINE__);
			}	
		}
	}
	

	if ((bsize = sysconf(_SC_PAGESIZE)) == -1) {
		err_sys("error in %s:%s:%d", __FILE__, "counter", __LINE__); 
	}
	char buff[bsize];

	word_count = 0;
	char_count = 0;
	line_count = 0;
	on_word = 0;
	while((nread = read_all(fd, buff, bsize)) != 0) {
		getcount(buff, nread);
	}
	close(fd);

}
