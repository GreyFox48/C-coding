/**
 * @file secs_to_date.c
 * @brief Prints the UTC and localtime.
 * @details Prints the number of seconds since epoch, as well as a 
 * formated dump of the struct tm from time.h and a formated time.  Prints both
 * the UTC and localtime.Uses the apue.h library to process errors.
 *
 * @author Matthew Olsen
 * @date February 15, 2018
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include "date.h"
#include <time.h>
#include "apue.h"

int main(int argc, char *argv[]) {
	struct tm *lt = NULL;
	char string[100];
	time_t t;

	if ((t = time(NULL)) == -1) {
                err_ret("error in %s:%s:%d", __FILE__ , 
                        "main", __LINE__); 
        }

	if ((lt = localtime(&t)) == NULL) {
                err_ret("error in %s:%s:%d", __FILE__ , 
                        "formated_local", __LINE__); 
        }

	formated_local(string, 100, t);

	printf("Number of seconds since the Epoch: %ld\n\n", t);
	printf("Localtime\n");
	printf("hours: %d\n", lt->tm_hour);
	printf("minutes: %d\n", lt->tm_min);
	printf("seconds: %d\n", lt->tm_sec);
	printf("year: %d\n", lt->tm_year);
	printf("month: %d\n", lt->tm_mon);
	printf("day of the month: %d\n", lt->tm_mday);
	printf("day of the week: %d\n", lt->tm_wday);
	printf("julian: %d\n", lt->tm_yday);
	printf("daylight savings time: %d\n", lt->tm_isdst);
	puts(string);

	formated_utc(string, 100, t);

	printf("\nCoordianted Univsersal Time (UTC)\n");
	printf("hours: %d\n", lt->tm_hour);
	printf("minutes: %d\n", lt->tm_min);
	printf("seconds: %d\n", lt->tm_sec);
	printf("year: %d\n", lt->tm_year);
	printf("month: %d\n", lt->tm_mon);
	printf("day of the month: %d\n", lt->tm_mday);
	printf("day of the week: %d\n", lt->tm_wday);
	printf("julian: %d\n", lt->tm_yday);
	printf("daylight savings time: %d\n", lt->tm_isdst);
	puts(string);

	return 0;
}
