#include "bst.h"
#include <string.h>
#include <stdio.h>

int compare(void *s, void *t)
{
        return strcmp((char *)s, (char *)t); //data specific
}


void print_node(void *key, void *data)
{
	printf("%s\n", (char *)key);
}


int main()
{
	BST_T dwarf = bst_new();
	bst_insert(dwarf, (void *)"Grumpy", NULL, compare);
   	bst_insert(dwarf, (void *)"Sleepy", NULL, compare);
	bst_insert(dwarf, (void *)"Doc", NULL, compare);
	bst_insert(dwarf, (void *)"Bashful", NULL, compare);
	bst_insert(dwarf, (void *)"Dopey", NULL, compare);
	bst_insert(dwarf, (void *)"Happy", NULL, compare);
	bst_insert(dwarf, (void *)"Sneezy", NULL, compare);
	printf("Inorder\n");
	bst_inorder(dwarf, print_node);
        return 0;
}

