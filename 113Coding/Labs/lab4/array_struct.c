/**
 * @file array_struct.c
 * @brief assigns values to a structure, and determines various qualitites
 * about the group.
 *
 * @author Matthew Olsen
 * @date September 30, 2015
 * @bug None
 * @todo Implement interface to enter information
 */

#include "array_struct.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	int min_height_index;
	int min_age_index;
	int max_height_index;
	int max_age_index;
	double average_age;
	double average_height;
	struct data_t data[SIZE];

	/* data initialization calls */
	fill_array(data, 0, 'A', 23, 74);
	fill_array(data, 1, 'B', 22, 64);
	fill_array(data, 2, 'C', 19, 68);
	fill_array(data, 3, 'D', 20, 76);
	fill_array(data, 4, 'E', 22, 62);

	/* find stuctures associated  with desired value */
	min_age_index = find_min_age(data, SIZE);
	min_height_index = find_min_height(data, SIZE);
	max_age_index = find_max_age(data, SIZE);
	max_height_index = find_max_height(data, SIZE);

	average_height = find_average_height(data, SIZE);
	average_age = find_average_age(data, SIZE);

	/* print all members of structure assoiciated with desired value */
	print_data(data[min_age_index]);
	print_data(data[min_height_index]);
	print_data(data[max_age_index]);
	print_data(data[max_height_index]);
	puts("");
	printf("The average height: %.2lf\n", average_height);
	printf("The average age: %.2lf\n", average_age);


	return 0;
}

/**
 * @param data[] the array to be populated
 * @param index the index of the id, years, and inches
 * @param id value of the data.subject variable
 * @param years value of the data.age variable
 * @param id value of the data.subject variable
 */
void fill_array(struct data_t data[], int index, char id, int years, int inches) {
	data[index].subject = id;
	data[index].age = years;
	data[index].height = inches;
}

/**
 * Finds the minimum age from a given data array
 * @param data the array of structures with the ages
 * @param size the size of the data array
 * @return the index of the minimum age
 */
int find_min_age(struct data_t data[], size_t size) {
	int age = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds index associated with lowest age */
		if(data[age].age > data[rep].age) {
			age = rep;
		}
	}

	return age;
}

/**
* Finds the minimum height from a given data array
 * @param data the array of structures with the height
 * @param size the size of the data array
 * @return the index of the minimum height
 */
int find_min_height(struct data_t data[], size_t size) {
	int height = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds index of structure with lowest height */
		if(data[height].height > data[rep].height) {
			height = rep;
		}
	}

	return height;
}

/**
 * Finds the maximum age from a given data array
 * @param data the array of structures with the ages
 * @param size the size of the data array
 * @return the index of the maximum age
 */
int find_max_age(struct data_t data[], size_t size) {
	int age = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds index associated with highest age */
		if(data[age].age < data[rep].age) {
			age = rep;
		}
	}

	return age;
}

/**
* Finds the maximum height from a given data array
 * @param data the array of structures with the height
 * @param size the size of the data array
 * @return the index of the maximum height
 */
int find_max_height(struct data_t data[], size_t size) {
	int height = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds index of structure with largest height */
		if(data[height].height < data[rep].height) {
			height = rep;
		}
	}

	return height;
}

/**
* Calculates the average height of the test subjects
* @param data the array of structures with the height
* @param size the size of the data array
* @return average height of the test subjects
*/
double find_average_age(struct data_t data[], size_t size) {
	double total = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds total value of ages */
		total += data[rep].age;
	}

	return total / size;
}


/**
* Calculates the average height of the test subjects
* @param data the array of structures with the height
* @param size the size of the data array
* @return average height of the test subjects
*/
double find_average_height(struct data_t data[], size_t size) {
	double total = 0;
	int rep;
	for(rep = 0; rep < size; rep++) {
		/* finds total value of heights */
		total += data[rep].height;
	}

	return total / size;
}

/**
 * prints the variables associated with a single data structure
 * @param data the structure containing the data
 */
void print_data(struct data_t data) {
	printf("The age of the subject: %d\n", data.age);
	printf("The height of the subject: %d\n", data.height);
	printf("The subject of the test subject: %c\n", data.subject);
	puts("");
}
