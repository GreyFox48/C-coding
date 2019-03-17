/**
 * @file date.c
 * @brief Impliments the date.h library.
 * @details Has const string arrays for the names of the months, as well as the
 * days of the week.  Indexing begins at 0.  Includes functions that return
 * formated strings of time in "Day, Month DayOfMonth, Year Hour:Minutes:Seconds
 * AM/PM" format. 
 *
 * @author Matthew Olsen
 * @date February 15, 2018
 * @todo Nothing
 * @bug none
 */

#include "apue.h"
#include <time.h>
#include <errno.h>
#include "date.h"
#include <string.h>

const char *Month[] = {
	"January", "February", "March", "April", "May", "June", "July", 
	"August", "September", "October", "November", "December" 
};

const char *Day[] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
	"Saturday"
};

/**
 * Creates a formated string of localtime in "Day, Month DayOfMonth, Year 
 * Hour:Minutes:Seconds AM/PM" format.
 * @param string the string to be formated.  Set to NULL in case of failure.
 * @param size the length of string
 * @param the seconds since epoch
 */
void formated_local(char *string, int size, time_t t){
	struct tm *lt = NULL;
        char temp[100];        

	if ((lt = localtime(&t)) == NULL) {
                /* sets string to NULL to signify error and returns */
                string = NULL;
                err_ret("error in %s:%s:%d", __FILE__ , 
                        "formated_local", __LINE__);
        }

        if (lt->tm_hour <= 12) { /* Different Print cases if AM or PM */
                sprintf(temp, "%s, %s %d, %d %02d:%02d:%02d AM", Day[lt->tm_wday], 
                        Month[lt->tm_mon], lt->tm_mday, lt->tm_year + 1900, 
                        lt->tm_hour, lt->tm_min, lt->tm_sec);
        } else {
                sprintf(temp, "%s, %s %d, %d %02d:%02d:%02d PM", Day[lt->tm_wday], 
                        Month[lt->tm_mon], lt->tm_mday, lt->tm_year + 1900, 
                        lt->tm_hour % 12, lt->tm_min, lt->tm_sec);
        }
        
        strncpy(string, temp, size);
}

/**
 * Creates a formated string of UTC in "Day, Month DayOfMonth, Year 
 * Hour:Minutes:Seconds AM/PM" format.
 * @param string the string to be formated.  Set to NULL in case of failure.
 * @param size the length of string
 * @param the seconds since epoch
 */
void formated_utc(char *string, int size, time_t t){
	struct tm *lt = NULL;
        char temp[100];        

	if ((lt = gmtime(&t)) == NULL) {
                /* sets string to NULL to signify error and returns */
                string = NULL;
                err_ret("error in %s:%s:%d", __FILE__ , 
                        "formated_local", __LINE__); 
        }

        if (lt->tm_hour <= 12) { /* Different Print cases if AM or PM */
                sprintf(temp, "%s, %s %d, %d %02d:%02d:%02d AM", Day[lt->tm_wday], 
                        Month[lt->tm_mon], lt->tm_mday, lt->tm_year + 1900, 
                        lt->tm_hour, lt->tm_min, lt->tm_sec);
        } else {
                sprintf(temp, "%s, %s %d, %d %02d:%02d:%02d PM", Day[lt->tm_wday], 
                        Month[lt->tm_mon], lt->tm_mday, lt->tm_year + 1900, 
                        lt->tm_hour % 12, lt->tm_min, lt->tm_sec);
        }
        
        strncpy(string, temp, size);
}
