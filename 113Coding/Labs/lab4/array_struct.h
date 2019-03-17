/**
 * @file array_struct.h
 * @brief Header file for array_struct.c
 * @details see array_struct.c
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None
 */

#ifndef ARRAY_STRUCT_H_
#define ARRAY_STRUCT_H_

#include <stdlib.h> 		/* for size_t declaration */


#define SIZE 5

struct data_t {

	int age;  /* age of the subject */
	int height;  /* height of subject in inches */
	char subject; 	/* one capital letter id for subject */

};

void fill_array(struct data_t data[], int index, char id, int years, int inches);
int find_min_age(struct data_t data[], size_t size);
int find_min_height(struct data_t data[], size_t size);
int find_max_age(struct data_t data[], size_t size);
int find_max_height(struct data_t data[], size_t size);
double find_average_age(struct data_t data[], size_t size);
double find_average_height(struct data_t data[], size_t size);
void print_data(struct data_t data);

#endif
