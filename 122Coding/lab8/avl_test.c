#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	struct avl_node_t *root = NULL;
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 8);
	root = insert(root, 25);
	root = insert(root, 40);
	inorder(root);
	return 0;
}

