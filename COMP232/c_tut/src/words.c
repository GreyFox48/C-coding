/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_NUM 256

int main(void) {
    char buffer[MAX_NUM];
    char *words[MAX_NUM];
    int i, num = 0;

    printf("Input the words to be read: ");
    for (i = 0; (i < MAX_NUM); i++, num++) {
        scanf("%s", buffer);
        if (0 == strcmp(buffer, "END")) break;
        words[i] = malloc(sizeof(char *) * (strlen(buffer) + 1));
        strcpy(words[i], buffer);
    }

    printf("The following %d words have been read:\n", num);
    for (i = 0; i < num; i++) {
        printf("%s\n", words[i]);
        free(words[i]); //what is alloced must be FREEED
    }
}

