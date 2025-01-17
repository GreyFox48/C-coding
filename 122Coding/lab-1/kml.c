/**
 * @file kml.c
 * @brief Creates the .kml and .out file for lab11.c
 * @details reads in the data from the locations.txt file, stores the data in
 * an array in a structure, converts DMS format to DD format, then prints to
 * locations.kml and locations.out.
 *
 * @author Matthew Olsen
 * @date Jan 30, 2016
 * @todo Nothing
 * @bugs Nope
 */

#include <string.h>
#include <stdio.h> //REMOVE THIS
#include <stdlib.h>
#include <errno.h>
#include "kml.h"

enum {INIT = 16, GROW = 2};

/**
 * Creates a pointer to a data_t structure, with an empty .data pointer
 * @return the pointer to the created data_t structure
 */
struct data_t *create_data(void) 
{
	struct data_t *data = malloc(sizeof(struct data_t));
        if (!data) {
                printf("Malloc failure in create_data. Goodbye!\n");
                exit(ALLOC_FAILURE);
        }
	data->max = INIT;
	data->nval = 0;
	data->data = NULL;
	return data;
}

/**
 * Reads in the locations.txt file and reads it line by line for city, location,
 * longitude and latitude data to store into the data_t structure.  Will also
 * malloc or realloc if the data->data array doesn't exist or is too short
 * @param data the pointer to the data_t structure
 * @param in the file locations.txt to obtain data from
 * @return the pointer to the populated data_t structure
 */
struct data_t *populate_data(struct data_t *data, FILE *in) 
{

	char buf[BUFF];
        
        //skip to fourth line
        fgets(buf, BUFF, in);
        fgets(buf, BUFF, in);
        fgets(buf, BUFF, in);
        
	
	while (fgets(buf, BUFF, in)) {

                data->nval = data->nval + 1;		

		if (data->nval > data->max) {
			data->data = realloc(data->data, data->max * GROW * sizeof(struct geo_city_t));

                        if (!data->data) {
                                printf("Realloc failure in pupulate_data. Goodbye!\n");
                                exit(ALLOC_FAILURE);
                        }

			data->max = data->max * GROW;
		} else if (!data->data) {
        		data->data = malloc(INIT * sizeof(struct geo_city_t));

                        if (!data) {
                                printf("Malloc failure in populate_data. Goodbye!\n");
                                exit(ALLOC_FAILURE);
                        }
                }

		set_city_state_country(data, buf);
		fgets(buf, BUFF, in); //next line will be latitude
		set_latitude(data, buf);
		fgets(buf, BUFF, in); //next line will be longitude
		set_longitude(data,buf);

	}
        return data;
}

/**
 * Reads the string buf to obtain the city and location data.  If the line
 * contains a state, stores the state in .state and .country = United States.
 * If location is not a state, then .state is set to null and location=.country
 * @param data the pointer to the data struct to store data in
 * @param buf the string containing the city and location data
 * @return none
 */
void set_city_state_country(struct data_t *data, char *buf)
{
        char *temp = NULL;
	int i = data->nval - 1; //to make indexing easier

        temp = strchr(buf, ',');
	//if after , is a state or a period (in D.C) or is Puerto Rico
	//comparison for state acronym is 3 instead of 2 to accuount for \n

        //remove newline character from buf
	remove_newline(buf);
 
	if(strlen(temp + 2) == 2 || strchr(temp, '.') || !strcmp("Puerto Rico", temp + 2)) {
		temp = strtok(buf, ",");
                //strlen(temp) + 1 is to make room for characters plus null terminator
                data->data[i].city = malloc(sizeof(char) * strlen(temp) + 1);
                if (!data->data[i].city) {
                        printf("Malloc failure in set_city_state_country. Goodbye!\n");
                        exit(ALLOC_FAILURE);
                }
		strncpy(data->data[i].city, temp, strlen(temp) + 1);
		temp = strtok(NULL, ",");
                data->data[i].state = malloc(sizeof(char) * strlen(temp) + 1);
                if (!data->data[i].state) {
                        printf("Malloc failure in set_city_state_country. Goodbye!\n");
                        exit(ALLOC_FAILURE);
                }
		// temp + 1 to not copy the space character
		strncpy(data->data[i].state, temp + 1, strlen(temp)); 
                data->data[i].country = malloc(sizeof(char) * strlen("United States") + 1);
                if (!data->data[i].country) {
                        printf("Malloc failure in set_city_state_country. Goodbye!\n");
                        exit(ALLOC_FAILURE);
                }
		strcpy(data->data[i].country, "United States");
	} else {
                temp = strtok(buf, ",");
                data->data[i].city = malloc(sizeof(char) * strlen(temp) + 1);
                if (!data->data[i].city) {
                        printf("Malloc failure in set_city_state_country. Goodbye!\n");
                        exit(ALLOC_FAILURE);
                }
                strncpy(data->data[i].city, temp, strlen(temp) + 1);
                //state not applicable to most other countries
                temp = strtok(NULL, ",");
                data->data[i].country = malloc(sizeof(char) * strlen(temp) + 1);
                if (!data->data[i].country) {
                        printf("Malloc failure in set_city_state_country. Goodbye!\n");
                        exit(ALLOC_FAILURE);
                }
                strncpy(data->data[i].country, temp + 1, strlen(temp) + 1);
        }
}

/**
 * Reads in a string, obtains the longitude in DMS format and 
 * converts to DD format
 * @param data the data structure to be populated
 * @param DMS the longitude string in DMS format
 * @return None
 */
void set_longitude(struct data_t *data, char *DMS)
{
        int degrees = 0;
        int minutes = 0;
        double DD = 0;
        char direction;
	int i = data->nval - 1; //for easier understanding of indexing

	remove_newline(DMS);

        sscanf(DMS, "%d %d %c", &degrees, &minutes, &direction);
	data->data[i].DMS_lon_deg = degrees;
	data->data[i].DMS_lon_min = minutes;
	data->data[i].DMS_lon_dir = direction;

        DD = degrees + (double)minutes / 60;

	//DD format is negative if west
        if (direction == 'W') { 
                DD*= -1;
        }
        data->data[i].DD_lon = DD;
}

/**
 * Reads in a string, obtains the longitude in DMS format and 
 * converts to DD format
 * @param data the data structure to be populated
 * @param DMS the latitude string in DMS format
 * @return None
 */
void set_latitude(struct data_t *data, char *DMS)
{
        int degrees = 0;
        int minutes = 0;
        double DD = 0;
        char direction;
	int i = data->nval - 1; //for easier understanding of indexing

	remove_newline(DMS);

        sscanf(DMS, "%d %d %c", &degrees, &minutes, &direction);
	data->data[i].DMS_lat_deg = degrees;
	data->data[i].DMS_lat_min = minutes;
	data->data[i].DMS_lat_dir = direction;

        DD = degrees + (double)minutes / 60;

	//DD format is negative if South
        if (direction == 'S') { 
                DD*= -1;
        }
        data->data[i].DD_lat = DD;
}

/**
 * Prints the contents of data->data to locations.out, in city|state|country|
 * Latitude|Longitude format
 * @param data the data pointer to the structure with informatin to be printed
 * @param output the pointer to locations.out
 * @return None
 */
void print_text(struct data_t *data, FILE *output)
{
        int i;

        //prints out the data in the proper format
        for (i = 0; i < data->nval; i++) {
                fprintf(output, "%s|%s|%s|", data->data[i].city, data->data[i].state, data->data[i].country);
		fprintf(output, "Latitude %d %d %c|", data->data[i].DMS_lat_deg, data->data[i].DMS_lat_min, data->data[i].DMS_lat_dir);
		fprintf(output, "Longitude %d %d %c\n", data->data[i].DMS_lon_deg, data->data[i].DMS_lon_min, data->data[i].DMS_lon_dir); 
        }
}

/**
 * Replaces the first newline character in as string with a newline character
 * @param buf the string possibly having a newline character
 * @return None
 */
void remove_newline(char *buf)
{
	char *temp= NULL; //to be used to hold position of newline character

	temp = strchr(buf, '\n');

	if (temp) {  //replace if null character if exists in string
		*temp = '\0';
	}
}

/**
 * Frees a data_t structure and all of its contents
 * @param data the pointer to the data structure
 * @return None
 */
void free_data(struct data_t *data)
{
	int i;

        //free the data in each array element
	for (i = 0; i < data->nval; i++) {
		free(data->data[i].city);
		free(data->data[i].state);
		free(data->data[i].country);
	}

        //free the array
	free(data->data);
        //free the structure
	free(data);
}

/**
 * Small function to call other functions to create the kml file
 * @param data the data structure containing to info to converted into kml
 * @param out the pointer to the file to print to
 * @return None
 */
void print_kml(struct data_t *data, FILE *out)
{
	kml_begin(out);
	kml_placemark(data, out);
	kml_end(out);
}

/**
 * Prints the elements of data->data into a kml compatible format
 * @param data the pointer to the data structure to be printed
 * @param out the pointer the file to print to 
 */
void kml_placemark(struct data_t *data, FILE *out) 
{
	int i;

        //print each data element in proper format
	for(i = 0; i < data->nval; i++) {
		fprintf(out, "   <Placemark>\n");
		if (data->data[i].state) {
			fprintf(out, "      <name>%s, %s</name>\n", data->data[i].city
			, data->data[i].state);
		} else {	
			fprintf(out, "      <name>%s, %s</name>\n", data->data[i].city
			, data->data[i].country);
		}
		fprintf(out, "      <Point>\n");
		fprintf(out, "         <coordinates>%.2lf,%.2lf,0</coordinates>\n", 
		data->data[i].DD_lon, data->data[i].DD_lat);
		fprintf(out, "      </Point>\n");
		fprintf(out, "   </Placemark>\n");
		fprintf(out, "\n");
	}

}

/**
 * The prints the standard beginning of the kml file
 * @param out the pointer of the file to be printd to
 * @return None
 */
void kml_begin(FILE *out) 
{
        //prints the beginning text needed for kml file
	fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(out, "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n");
	fprintf(out, "<Document>\n");
	fprintf(out, "   <name>Mystery Locations</name>\n\n");
}

/**
 * The prints the standard ending of the kml file
 * @param out the pointer of the file to be printd to
 * @return None
 */
void kml_end(FILE *out)
{
        //ends the file
	fprintf(out, "</Document>\n");
	fprintf(out, "</kml>");
}
