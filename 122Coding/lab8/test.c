/**
 * @file greek.c
 * @brief Stores a given greek god file in an avl tree.
 * @details None
 *
 * @date May 7, 2016
 * @author Matthew Olsen
 * @bugs None.
 * @todo Nothing
 */ 

#include <string.h>
#include <stdio.h>
#include "avl.h"
#include <assert.h>
#include <stdlib.h>

#define LEN 1024

int keycmp(void *str1, void *str2);
void printnode(void *key, void *value);
void ufree(void *key, void *value);
void print_key(void *key, void *value);

int main(void)
{
        char *temp_key;
        char *temp_value;
        char input[LEN];
        char *find = NULL;
        char *value = NULL;
        FILE *fp = fopen("greek.txt", "r");
        assert(fp);
        AVL_T avl = avl_new();
        
        /* insert the data into the avl tree */
        while (fgets(input, LEN, fp)) {
                temp_key = malloc(sizeof(char) * strlen(input));
                assert(temp_key);
                strncpy(temp_key, input, strlen(input));                
                temp_key[strcspn(temp_key, "\n")] = 0;
                fgets(input, LEN, fp);
                temp_value = malloc(sizeof(char) * strlen(input));
                assert(temp_value);
                strncpy(temp_value, input, strlen(input));                
                temp_value[strcspn(temp_value, "\n")] = 0;
                avl_insert(avl, temp_key, temp_value, keycmp);
        }

        avl_inorder(avl, printnode);
        printf("\n\n");
        
        printf("\tPreorder\n");
        avl_preorder(avl, print_key);
        printf("\tPostorder\n");
        avl_postorder(avl, print_key);
        printf("\n\n");
        
        find = "Dionysus";
        value = avl_find(avl, find, keycmp);        
        if (value != NULL) {
                printf("%s\n", value);
        } else {
                printf("%s could not be found.\n", find);
        }
        printf("\n\n");
        
        find = "Jupiter";
        value = avl_find(avl, find, keycmp);        
        if (value != NULL) {
                printf("%s\n", value);
        } else {
                printf("%s could not be found.\n", find);
        }
        printf("\n\n");
        
        avl_delete(avl, "Hestia", keycmp, ufree);
        avl_delete(avl, "Artemis", keycmp, ufree);
        avl_delete(avl, "Hades", keycmp, ufree);
        avl_delete(avl, "Pandora", keycmp, ufree);
        avl_delete(avl, "Hephaestus", keycmp, ufree);
        avl_delete(avl, "Zeus", keycmp, ufree);
        
        avl_inorder(avl, print_key);

        /* free everything */
        avl_free(avl, ufree);
        fclose(fp);
        
        return 0;
}

/**
 * The user provided compare function
 * @param str1 the first string to be compared
 * @param str2 the second string to be compared
 * @return less than 0 if str1 is less than 0, 0 if equal, or greater than 0
 * if str1 is greater than str2.
 */
int keycmp(void *str1, void *str2)
{
        return strcmp((char *) str1, (char *) str2);
}

/**
 * Prints both the key and the value of the node
 * @param key the key to be printed
 * @param value the value to be printed
 */
void printnode(void *key, void *value)
{
        printf("%s\n%s\n", (char *)key, (char *)value);
}

/**
 * The user provided free function for both the key and value
 * @param key the key to be printed
 * @param value the value to be printed
 */
void ufree(void *key, void *value)
{
        free((char *)key);
        free((char *)value);
}

/**
 * User print function that only prints the key value
 * @param key the key to be printed
 * @param value the value to not be printed
 */
void print_key(void *key, void *value)
{
        printf("%s\n", (char *)key);
}

