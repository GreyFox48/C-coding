/**
 * @file scrabble_lookup.c
 * @brief User interface to determine if a word exists in the scrabble dictionary
 * @details Utilizes a chained hash table to load the file.  The first argument should be the
 * hash table size and if "table" is inputed as the second arguemnt it will output the hash table
 *
 * @date April 17, 2016
 * @author Matthew Olsen
 * @bugs None
 * @todo Nothing
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define LEN 128
#define INVALID_INPUT 1000

unsigned djb_hash(void *key);

struct node_t {
        char *word; /* dictionary word */
        struct node_t *next; 
};

struct list_t {
        int nnodes; /* number of nodes list contains */
        struct node_t *head; /*head of the list */
};

void tolowercase(char *s);
void rstrip(char *s);
void hash_word(struct list_t **dict, char *s, size_t size);
unsigned djb_hash(void *key);
void free_dict(struct list_t **dict, size_t size);
void print_dict(struct list_t **dict, size_t size);
void print_lfactor(struct list_t **dict, size_t size);
int find_word(struct list_t **dict, char *s, size_t size);

int main(int argc, char *argv[]) 
{
	char buf[LEN];
	int i;
	FILE *fp = fopen("scrabble.txt", "r");
	assert(fp);

	/* get and check user input for table size */
        size_t tbl_size = strtol(argv[1], NULL, 10);
        if (tbl_size == 0) {
        	printf("Please provide an integer argument for the size of "
        		"the hash table.\n");
        	exit(INVALID_INPUT);
        }

        /* load and create table */
        struct list_t **dict = malloc(sizeof(struct list_t *) * tbl_size);
        assert(dict);
        
        for (i = 0; i < tbl_size; i++) {
                dict[i] = malloc(sizeof(struct list_t));
                	assert(dict[i]);
                dict[i]->nnodes = 0;
                dict[i]->head = NULL;
        }

        while (fgets(buf, LEN, fp)) {
        	rstrip(buf);
        	hash_word(dict, buf, tbl_size);
        }

        /* hidden debugging function, use by giving table size then "table"
         * as arguments */
        if (argc == 3 && !strncmp(argv[2], "table", 5)) {
        	print_dict(dict, tbl_size);
		print_lfactor(dict, tbl_size);
		free_dict(dict, tbl_size);
		fclose(fp);
		return 0;
        }

        /* menu for user input */
        while (1) {
        	printf("Please input a word to look up in the scrabble dictionary "
        		", or q to quit: ");
        	fgets(buf, LEN, stdin);
        	rstrip(buf);
        	tolowercase(buf);
        	if (find_word(dict, buf, tbl_size) != -1) {
	        	printf("%s exists in the scrabble dictionary.\n", buf);
	        } else if (!(strncmp(buf, "q", 1))) {
	        	free_dict(dict, tbl_size);
			fclose(fp);
			return 0;
	        } else {
	        	printf("%s does not exist in the scrabble dictionary.\n", buf);
	        }

        }

        /* This should not happen */
        printf("HOW COULD THIS HAPPEN!?\n");
        free_dict(dict, tbl_size);
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
 * Places a word into an array of list_t pointers, utilizing
 * the djb hash function.
 * @param dict the array of list_t pointer pointers.  Will act as an hashing
 * table.
 * @param s the word to be be hashed.
 * @param size the size of the dict array.
 */
void hash_word(struct list_t **dict, char *s, size_t size)
{
	int key = djb_hash(s) % size;

	struct node_t *node = malloc(sizeof(struct node_t));
		assert(node);
	node->word = malloc(sizeof(char) * (strlen(s) + 1));
		assert(node->word);
	strncpy(node->word, s, strlen(s));
	node->next = NULL;

	node->next = dict[key]->head;
	dict[key]->head = node;
	dict[key]->nnodes++;
}

/**
 * Frees an array of list_t pointers, and all of its contents.
 * @param dict the array of list_t pointers
 * @param size the size of the dict array
 */
void free_dict(struct list_t **dict, size_t size)
{
	struct node_t *current = NULL, *prev = NULL;
	int i;

	/* free the lists and nodes*/
	for (i = 0; i < size; i++) {
		current = dict[i]->head;
		while (current) {
			prev = current;
			current = current->next;
			free(prev->word);
			free(prev);
		}	
		free(dict[i]);	
	}

	free(dict);	
}

/**
 * Prints the dictionary in the specifified format
 * @param dict the list_t pointer array
 * @size the size of the dict array
 */
void print_dict(struct list_t **dict, size_t size)
{
	int i, j;
	struct node_t *node = NULL;

	for (i = 0; i < size; i++) {
		node = dict[i]->head;
		printf("%5d: ", i);
		for (j = 0; j < dict[i]->nnodes; j++) {
			 printf(j == dict[i]->nnodes - 1 ? "%s" : "%s, ",
			     node->word);
			 node = node->next;
		}
		printf("\n");
	}
}

/**
 * Calculates the load factor of a list_t pointer hash table
 * @param dict the hash table to calculate the load for
 * @param size the size of the table
 */
void print_lfactor(struct list_t **dict, size_t size) 
{
	int i;
	int load = 0;

	for (i = 0; i < size; i++) {
		load += dict[i]->nnodes;
	}

	printf("table size %zu load factor %.2lf\n", size, (double)load / (double)size);

}

/**
 * Determines if a given word exists in the dictionary
 * @param dict the list_t pointer array to look through
 * @param s the word to search for
 * @param size the size of dict
 * @return The index of the linked list the word is found in or -1 for failure
 */
int find_word(struct list_t **dict, char *s, size_t size)
{
	int key = djb_hash(s) % size;
	struct node_t *node = dict[key]->head;
	int i;

	for (i = 0; i < dict[key]->nnodes; i++) {
		if (!(strncmp(node->word, s, strlen(s)))) {
			return key;
		}
		node = node->next;
	}

	return -1;
}