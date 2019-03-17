/**
 * @file kml.h
 * @brief Header file for kml.c.
 * @details See kml.c for implementation details.
 *
 * @author Matthew Olsen
 * @date Febuary 02, 2016
 * @todo Nothing
 * @bug none
 */

#ifndef _KML_H_
#define _KML_H_

#define BUFF 132
#define ALLOC_FAILURE 100

struct geo_city_t {
	char *city;
	char *state;
	char *country;
	double DD_lon; //DD longitue and latitude
	double DD_lat;
	int DMS_lon_deg; //DMS Longitude and Latitude
	int DMS_lon_min;
	char DMS_lon_dir;
	int DMS_lat_deg;
	int DMS_lat_min;
	char DMS_lat_dir;
};

struct data_t {
	int nval;  // number of cities inputed in array
	int max;  //max number of indexes in array
	struct geo_city_t *data;  //head of array
};

struct data_t *create_data(void);
struct data_t *populate_data(struct data_t *data, FILE *in);
void set_longitude(struct data_t *data, char *DMS);
void set_latitude(struct data_t *data, char *DMS);
void set_city_state_country(struct data_t *data, char *buf);
void print_text(struct data_t *data, FILE *output);
void remove_newline(char *buf);
void free_data(struct data_t *data);
void print_kml(struct data_t *data, FILE *out);
void kml_placemark(struct data_t *data, FILE *out);
void kml_begin(FILE *out);
void kml_end(FILE *out);

#endif
