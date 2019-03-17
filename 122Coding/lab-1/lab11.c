/**
 * @file lab11.c
 * @brief Reads in a text file and outputs into another text file and a .kml
 * @details Takes in a file called locations.txt and outputs to two seperate
 * files files, locations.out and locations.kml. Locations.out is the data
 * from locations.txt and prints the data pipe seperated. Locations.kml is
 * is the data from locations.txt formated into a kml file
 *
 * @author Matthew Olsen
 * @date Jan 30, 2016
 * @todo Nothing
 * @bugs Nope
 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "kml.h"

int main(void) {
	
        //create the data structure
	struct data_t *data = create_data();

        //open the files first
	FILE *in = fopen("locations.txt", "r");
	if (!in) {
		puts("Couldn't open locations.txt.  Goodbye!\n");
		exit(ENOENT);
	}

	FILE *loc_out = fopen("locations.out", "w");
	if (!loc_out) {
		puts("Couldn't open locations.out.  Goodbye!\n");
		exit(EIO);
	}

	FILE *loc_kml = fopen("locations.kml", "w");
	if (!loc_kml) {
		puts("Couldn't open locations.txt.  Goodbye!\n");
		exit(ENOENT);
	}
        //retrieve the data from the files
	data = populate_data(data, in);
        print_text(data, loc_out);	
        print_kml(data, loc_kml);

        //free the alloced memory
        free_data(data);
        free(in);
        free(loc_out);
        free(loc_kml);

        return 0;
}
