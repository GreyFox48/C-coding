/**
 * @file myenv.c
 * @brief Simulates the env command
 * @details Mimicks the use of the env command.  Supports the commands -i, -, 
 * -h, and -v.  Changed the environment variables if specified. Uses apue.h 
 * functions to ensure that system calls succeeded. 
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "apue.h"
#include <stdbool.h>
#include <ctype.h>

char **new_environ(int argc, char *argv[]);
void clear_env(char **env);
void modify_env(int argc, char *argv[]);
void call_system(int argc, char *argv[]);
void print_environ();

extern char **environ;
#define MAX_CMD_LEN 8124

int main(int argc, char *argv[])
{
	char **env = NULL;	
	int i = 0;
	bool bi = false;

	/* print_environ(); //testing */

	/* print the environ only */
	if (argc == 1) {
		print_environ();
		return 0; /* nothing to do */
	}

	for (i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-h", 2) == 0) {
			printf("myenv - run a program in a modified environment.\n");
			printf("\t-i, - clears the environment.\n");
			printf("\t-h displays the help function.\n");
			printf("\t-v displays the version.\n");
			printf("\tcommands with name=value are" 
				"taken as environment variables.\n");
			return 0;
		} else if (strncmp(argv[i], "-i", 2) == 0) {
			bi = true;
			env = new_environ(argc, argv);
		} else if (strncmp(argv[i], "-", 2) == 0) {
			bi = true;
			env = new_environ(argc, argv);
		} else if (strncmp(argv[i], "-v", 2) == 0) {
			printf("myenv (TIRED STUDENT) VERSION 1\n");
			printf("Creator: Matthew Olsen\n");
			return 0;
		}
	}

	/* lazy check for lack of commandline options */
	if (bi == false) {
		modify_env(argc, argv);
	}	
	
	call_system(argc, argv);

	/* print_environ(); //testing */

	/* memory free function */
	if (bi == true) {
		clear_env(env);		
	}

	return 0;
}

/**
 * Creates a brand new envirnment for the user.  First clears it, and then
 * creates a new array of strings to assign to the environ.
 * @para argc The number of arguments sent in by the user
 * @param The array of the argument strings
 */
char **new_environ(int argc, char *argv[])
{
	int i = 0;
	int count = 0; /*acts as indexing of the environ array */
	char **newenv = malloc((count + 1) * sizeof(char *));
	assert(newenv != NULL);	
	int t = 0;
	
	if ((t = clearenv()) != 0) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}
	for (i = 0; i < argc; i++) {
		if(strchr(argv[i], '=') != NULL) { /* assume all lines with '='
			are env variables */
			count++;
			newenv = realloc(newenv, (count + 1) * sizeof(char *));
			assert(newenv != NULL);
			newenv[count - 1] = malloc((strlen(argv[i]) + 1) 
				* sizeof(char));
			strncpy(newenv[count - 1], argv[i], strlen(argv[i]) + 1);
		}
	}

	newenv[count] = NULL; /* set last string to NULL in the array */
	environ = newenv;

	return newenv;
}

/**
 * Simply modifies the environment of the user by using setenv().  
 * @para argc The number of arguments sent in by the user
 * @param The array of the argument strings
 */
void modify_env(int argc, char *argv[])
{
	char buff[MAX_CMD_LEN];
	char str1[MAX_CMD_LEN];
	char str2[MAX_CMD_LEN];
	char *ptr = NULL;
	int i = 0;
	int t = 0;

	for (i = 0; i < argc; i++) {
		/* assume all lines with '=' are command line arguments */
		ptr = strchr(argv[i], '=');
		if (ptr != NULL) {
			/* don't wish to change argv, so copy to buff */
			strncpy(buff, argv[i], strlen(argv[i]) + 1);
			ptr = strchr(buff, '=');
			*ptr = '\0';
			strncpy(str1, buff, strlen(buff) + 1);
			strncpy(str2, ptr+1, strlen(ptr+1) + 1);
			if ((t = setenv(str1, str2, 1)) != 0) {
                		err_sys("error in %s:%s:%d", __FILE__, 
				"main", __LINE__); 
        		}
		}
	}
}

/** 
 * Frees the custom made environment the user specifed.
 */
void clear_env(char **env)
{
	int i = 0;

	for(i = 0; env[i] != NULL; i++) {
		free(env[i]);
	}
	free(env);
}

/**
 * Implements the COMMANDS part of the env command.
 * @para argc The number of arguments sent in by the user
 * @param The array of the argument strings
 */
void call_system(int argc, char *argv[])
{
	int i = 0;
	char buff[MAX_CMD_LEN] = {"\0"}; /* to prevent jump from undeclared */
	char temp[MAX_CMD_LEN];
	char *end = NULL;
	int t = 0;

	/* skip the program invocation */
	for (i = 1; i < argc; i++) {
		/* skip to commands */
		if( (strchr(argv[i], '=') == NULL) 
		&& (strchr(argv[i], '-') == NULL)) {
			break;
		}
	}

	/* get the commands */
	for ( ; i < argc; i++) {		
		sprintf(temp, "%s ", argv[i]);
		strcat(buff, temp);		
	}

	/* Try to detect if there were no commands */
	if(strlen(buff) == 0) {
		return;
	}

	/*triming the last space */
	end = buff + strlen(buff) - 1;
  	while(end > buff && isspace((unsigned char)*end)){
		end--;
	}
	*(end+1) = 0;

	/*finally, call the system */
	if ((t = system(buff)) != 0) {
		err_sys("error in %s:%s:%d", __FILE__, "main", __LINE__); 
	}
	

	return;
}

/**
 * Simply prints the current environment.
 */
void print_environ()
{
	char **env = NULL;

	for(env = environ; *env != NULL; env++) {
		puts(*env);
	}
	return;
}
