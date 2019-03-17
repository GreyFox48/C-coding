/**
 * @file lab4_q4.c
 * @brief Determines the Zodiac sign of a given birthday.
 * @details Can input a birthday multiple times.
 *
 * @author Matthew Olsen
 * @date 30 September 2015
 * @bug None
 */

#include <stdio.h>
#include <stdlib.h>

#define QUIT 0
#define CONTINUE 1

enum month
{
        JAN = 1, FEB, MAR, APR, MAY, JUNE, JUL, AUG, SEPT, OCT, NOV, DEC
};

unsigned short julian_date(unsigned short day, unsigned short month, unsigned short year);
void print_date(unsigned short day, unsigned short month, unsigned short year);

int main (void)
{

        unsigned short month = JAN;
        unsigned short day = 24;
        unsigned short year = 1997;
        unsigned short julian_birthday = 0;
        unsigned short menu = 1; /* ensure first time runs without continue prompts */

        printf("This program finds the Zodiac sign for a given birthday.\n");

        while(1) {
                switch (menu) {
                case CONTINUE:
                        printf("Enter the date in month/day/year format: ");
                        scanf("%hu/%hu/%hu", &month, &day, &year);

                        julian_birthday = julian_date(day, month, year);

                        /* Capricorn, Aquarius, then Pisces */
                        /* zodiac sign dates cannot be entirely hardcoded due to possiblity of leap year
                         *  and is thus calculated using a function */
                        if(julian_birthday <= julian_date(20, JAN, year)) {
                                printf("The Zodiac sign for ");
                                /* user inputed date to be printed in special format: Month day, Year */
                                print_date(day, month, year);
                                printf(" is Capricorn.\n");
                        } else if(julian_birthday <= julian_date(19, FEB, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Aquarius.\n");
                        } else if(julian_birthday <= julian_date(20, MAR, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Pisces.\n");
                        /* Aries, Taurus, then Gemini */
                        } else if(julian_birthday <= julian_date(20, APR, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Aries.\n");
                        } else if(julian_birthday <= julian_date(21, MAY, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Taurus.\n");
                        } else if(julian_birthday <= julian_date(21, JUNE, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Gemini.\n");
                        /* Cancer, Leo, then Virgo */
                        } else if(julian_birthday <= julian_date(22, JUL, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Cancer.\n");
                        } else if(julian_birthday <= julian_date(22, AUG, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Leo.\n");
                        } else if(julian_birthday <= julian_date(23, SEPT, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Virgo.\n");
                        /* Libra, Scorpio, then Sagittarius */
                        } else if(julian_birthday <= julian_date(23, OCT, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Libra.\n");
                        } else if(julian_birthday <= julian_date(22, NOV, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Scorpio.\n");
                        } else if(julian_birthday <= julian_date(21, DEC, year)) {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Sagittarius.\n");
                        } else {
                                printf("The Zodiac sign for ");
                                print_date(day, month, year);
                                printf(" is Capricorn.\n");
                        }

                        break;

                case QUIT:
                        printf("Goodbye!\n");
                        exit(EXIT_SUCCESS);
                default:
                        printf("I do not understand that input.\n");
                }

                printf("Enter 1 to enter another birthday, or 0 to quit: ");
                scanf("%hu", &menu);                
        }

        return 0;
}

/**
 * Calculates the Julian date for the day of the year.  Takes into account leap years
 * @param day The given day
 * @param month the month of the year
 * @param year the year
 * @return the julian date, a number 1-365 or 366 depending on given year
 */
unsigned short julian_date(unsigned short day, unsigned short month, unsigned short year) {
        int rep;
        unsigned short julian_date = day;
        /* first element is placeholder, to align months in array with actual month number */
        unsigned short days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                days_in_month[2] = 29;
        }

        /* month + 1 accounts array being shifted up one index */
        for(rep = 1; rep < month + 1; rep++) {
                julian_date += days_in_month[rep];
        }

        return julian_date;
}

/**
 * Prints the date to terminal, in a "Day Month, Year" Format
 * @param day The given day
 * @param month the month of the year
 * @param year the year
 */
void print_date(unsigned short day, unsigned short month, unsigned short year) {
        switch (month) {
        case JAN:
                printf("January %hu, %hu", day, year);
                break;
        case FEB:
                printf("Febuary %hu, %hu", day, year);
                break;
        case MAR:
                printf("March %hu, %hu", day, year);
                break;
        case APR:
                printf("April %hu, %hu", day, year);
                break;
        case MAY:
                printf("May %hu, %hu", day, year);
                break;
        case JUNE:
                printf("June %hu, %hu", day, year);
                break;
        case JUL:
                printf("July %hu, %hu", day, year);
                break;
        case AUG:
                printf("August %hu, %hu", day, year);
                break;
        case SEPT:
                printf("September %hu, %hu", day, year);
                break;
        case OCT:
                printf("October %hu, %hu", day, year);
                break;
        case NOV:
                printf("November %hu, %hu", day, year);
                break;
        case DEC:
                printf("December %hu, %hu", day, year);
                break;
        default:
                printf("Error:  print_date switch fell through completely.\n");
        }
}
