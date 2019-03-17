/**
 * @file date.h
 * @brief Header file for date.c.
 * @details See date.c for implementation details.
 *
 * @author Matthew Olsen
 * @date February 15, 2018
 * @todo Nothing
 * @bug none
 */

#include <time.h>

#ifndef DATE_H_
#define DATE_H_

/* figured having predefined month and date strings to be usefull for later */
extern const char *Month[12]; 
extern const char *Day[7];

void formated_local(char *string, int size, time_t t);
void formated_utc(char *string, int size, time_t t);

#endif
