#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include <assert.h>

  
#define T BST_T

struct T {

	int count;

	struct node_t {
		void *key;
		void *value; 	/* additional data */
		struct node_t *left;
		struct node_t *right;
	} *head;
 
};

T bst_new(void)
{
   T bst;
   bst = malloc(sizeof(struct T));
   assert(bst);
   
   bst->count = 0;
   bst->head = NULL;
   
   return bst;
}
       
/* internal use only -- need to recursively find node to insert after  */
int insert(struct node_t **node, void *key, void *value, int (*ucmp)(void *, void *)) 
{
	struct node_t *tmp;
	int comp;

	tmp = *node;

	if (tmp == NULL) {
		tmp = malloc(sizeof(struct node_t));
		assert(tmp);
		tmp->key = key;
		tmp->value = value;

		tmp->left = tmp->right = NULL;
		*node = tmp;
		return 0; //success
	 
	}

	comp = (*ucmp)(key, tmp->key);
	
	if (comp == 0) {
		return -1; 	/* key already exists in tree - don't add  */
	}
   
	if (comp < 0) {
		insert(&tmp->left, key, value, ucmp);
	}
	else {
		insert(&tmp->right, key, value, ucmp);
	}
	
	return 0;
}

/* user provided compare function ucmp */
int bst_insert(T bst, void *key, void *value, int (*ucmp)(void *, void *))
{

	assert(bst); 	/* does tree exist? */
	
	if (insert(&bst->head, key, value, ucmp) == 0) {
		bst->count++;
		return 0;
	}
	else {
		return -1; 	/* key already exists */
	}
	
}


/* (*uprint) user provided print function */
void inorder(struct node_t *node, void (*uprint)(void *, void *))
{
   if (node != NULL) {
	   inorder(node->left, uprint);
	   uprint(node->key, node->value);
	   inorder(node->right, uprint);
   }
}


/* (*uprint) user provided print function */
void bst_inorder(BST_T bst, void (*uprint)(void *, void *))
{
	inorder(bst->head, uprint);
}

