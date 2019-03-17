/**
 * @file sundays.c
 * @brief Determines the number of sundays that are the
 * first day of the month between two given years.
 * @details Currently, the startyear is hardcoded to be 1901.
 *
 * @author Matthew Olsen
 * @date October 8, 2015
 * @bug None None
 * @todo Make flexible starting date
 */


#include <stdlib.h>
#include <stdio.h>

enum Day
{
        SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

int main(void)
{
        int startday = TUESDAY; /* first day of 1901 is a tuesday */
        int startyear = 1901;
        int endyear = 2000;
        int totaldays = startday; /* shifts totals days by starting day for
                                     later calculations */
        int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31,
                 31, 30, 31, 30, 31};
        int sundays;
        int i;
        int j;

        for(i = startyear; i <= endyear; i++){ /* total amount of days */
                if((i % 4 == 0 && i % 100 != 0) || i % 400 == 0){
                        days_in_month[1] = 29;
                } else {
                        days_in_month[1] = 28;
                }
                for(j = 0; j < 12; j++){
                        if ((totaldays % 7) == SUNDAY){ /* Calculates if
                                remaining day would include a Sunday */                                
                                sundays++;
                        }
                        totaldays += days_in_month[j];
                }

        }

        printf("The Number of Sundays between the years %d ", startyear);
        printf("and %d inclusive is %d.\n", endyear, sundays);

        return 0;
}
