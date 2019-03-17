/**
 * @file state_hash.c
 * @brief User interface to print postal address name from a given abbreviation
 * @details Utilizes a hash table to store the values.  Type "q" to quit or
 * "table" to print the table
 *
 * @date April 17, 2016
 * @author Matthew Olsen
 * @bugs None
 * @todo Nothing
 */ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LEN 4096
#define SIZE 200

struct postal_t {
        char *abrv; /*two digit abbreviation, capitalized */
        char *name; /*name in start case */
};

void tolowercase(char *s);
void rstrip(char *s);
void capitalized(char *s);
void freepostal(struct postal_t *postal, size_t size);
unsigned djb_hash(void *key);
void print_hash_table(struct postal_t *postal, size_t size);
int insert_key(struct postal_t *postal, struct postal_t new, size_t size);
int find_key(struct postal_t *postal, char *s, size_t size);

int main(int argc, char *argv[])
{
        char buf[LEN], temp[LEN];
        struct postal_t *postal = malloc(SIZE * sizeof(struct postal_t));
        	assert(postal);
        struct postal_t temp_post;
        int i = 0;
        int index = -1;

	FILE *fp = fopen("postal", "r");
	assert(fp);	

	while(fgets(buf, LEN, fp)) {
		/* copy line contents to tempary structure */
		/* copy the postal code name */
		memcpy(temp, buf, strlen(buf) - 3);
		rstrip(temp);
		tolowercase(temp);
		capitalized(temp);
		temp_post.name = malloc((strlen(temp) + 1) * sizeof(char));
			assert(temp_post.name);
		strncpy(temp_post.name, temp, strlen(temp) + 1);
		/* copy the postal code abbrevition */
		strncpy(temp, buf + strlen(buf) - 3, strlen(buf + strlen(buf) - 3) + 1);
		rstrip(temp);
		temp_post.abrv = malloc((strlen(temp) + 1) * sizeof(char));
			assert(temp_post.abrv);
		strncpy(temp_post.abrv, temp, strlen(temp) + 1);

		assert(insert_key(postal, temp_post, SIZE));
		i++;
        }

        while (1) {
        	printf("Enter a two-digit state abbrevition (q to quit): ");
        	fgets(buf, LEN, stdin);
        	rstrip(buf);
        	if (strlen(buf) == 2) {
        		index = find_key(postal, buf, SIZE);
        		if (index != -1) {
        			printf("%s\n", postal[index].name);
        		} else {
        			printf("State not found\n");
        		}
        	} else if (!(strncmp(buf, "q", 1))) {
        		freepostal(postal, SIZE);
		        fclose(fp);
		        return 0;
        	} else if (!(strncmp(buf, "table", strlen("table")))) {
        		print_hash_table(postal, SIZE);
        	} else {
        		printf("Enter two capitalized letters to find the "
        			"corresponding postal name, q to quit the "
        			"program,\n or table to print the table\n");
        	}
        }

        printf("HOW COULD THIS HAPPEN!?\n");
        freepostal(postal, SIZE);
        fclose(fp);

        return 0;
}

/**
 * Converts strings to lowercase strings
 * @param s the string to be converted
 */
void tolowercase(char *s)
{
        while (*s != '\0') {
                *s = tolower(*s);
                s++;
        }
}

/**
 * Trims off whitespace from the right of a string
 * @param s the string to be trimmed
 */
void rstrip(char *s)
{         
        char *endpoint = strlen(s) - 1 + s;
        while (isspace(*endpoint)) {
                endpoint--;
        }
        /* off by one error */
        endpoint++;
        *endpoint = '\0';        
}

/**
 * Converts the first letter of a word to capitalized letters.
 * Assumes that the given string is trimmed.
 * @param s the string to be capitalized
 */
void capitalized(char *s) 
{
	int i;
	s[0] = toupper(s[0]);

	for (i = 1; i < strlen(s); i++) {
		if (isalpha(s[i]) && isspace(s[i - 1])) {
			s[i] = toupper(s[i]);
		}
	}
}

/**
 * Frees a postal_t array
 * @param postal the table to be freed
 * @param size the size of the postal array
 */
void freepostal(struct postal_t *postal, size_t size)
{
	int i;
	for (i = 0; i < size; i++) {
		free(postal[i].name);
		free(postal[i].abrv);
	}
	free(postal);
}

/**
 * Creates a djb-calculated key value from a given null terminated array
 * @param key the key to create a key value for 
 */
unsigned djb_hash(void *key)
{
	unsigned char *p = key;
	unsigned h = 0;

	while (*p) {
		h = 33 * h + *p;
		p++;
	}

	return h;
}

/**
 * Prints the hash table, skipping over unassigned values
 * @param postal the postal structure array to be printed
 * @param size the size of the array
 */
void print_hash_table(struct postal_t *postal, size_t size)
{
	int i;
	for (i = 0; i < size; i++) {
		if(postal[i].name && postal[i].abrv) {
			printf("i = %d\n", i);
			printf("%s\t%s\n", postal[i].abrv, postal[i].name);
		}
	}
}

/**
 * Inserts a given postal_t structure into a postal_t array, using djb hashing.
 * @param postal the hash table of postal elements
 * @param new the element to be inserted into the table
 * @param size the size of postal
 * @return 1 for a successful insert, 0 for failure.
 */
int insert_key(struct postal_t *postal, struct postal_t new, size_t size)
{
	int i, index;
	int key = djb_hash(new.abrv) % size;

	for (i = 0; i < size; i++) {
		index = (key + i * i) % size;
		if(!(postal[index].name && postal[index].abrv)) {
			postal[index] = new;
			return 1;
		}

	}

	return 0;
}

/**
 * finds the index from a hashed postal array of a given key
 * @param postal the hashed table of postal structures
 * @param s the key to search for
 * @param the size of the postal hash table
 * @return the index upon success, -1 for failure
 */
int find_key(struct postal_t *postal, char *s, size_t size)
{
	int i, index;
	int key = djb_hash(s) % size;

	for (i = 0; i < size; i++) {
		index = (key + i * i) % size;
		if(postal[index].name && postal[index].abrv) {
			if (!(strncmp(postal[index].abrv, s, strlen(s)))) {
				return index;
			}
		}
	}

	return -1;
}