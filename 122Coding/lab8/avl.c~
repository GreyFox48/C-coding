/**
 * @file avl.c
 * @brief Implements a avl tree.
 * @details The avl tree nodes hold void pointers, and thus data comparison and
 * freeing are depedent upon user provided functions
 *
 * @date May 7, 2016
 * @author Matthew Olsen
 * @bugs None.
 * @todo Nothing
 */ 

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"		

#define T AVL_T

struct T {
	int count;

	struct avl_node_t {
		void *key;
		void *value;
		int height;		/* balance factor */
		struct avl_node_t *left;
		struct avl_node_t *right;
	} *head;
};

struct avl_node_t *single_rotate_left(struct avl_node_t *x);
struct avl_node_t *single_rotate_right(struct avl_node_t *w);
struct avl_node_t *double_rotate_left(struct avl_node_t *z);
struct avl_node_t *double_rotate_right(struct avl_node_t *z);
struct avl_node_t *insert(struct avl_node_t *root, void *key, void *value, int (*ucmp)(void *a, void *b));
struct avl_node_t *delete_node(struct avl_node_t *root, void *key, int (*ucmp)(void *a, void *b), void (*ufree)(void *key, void *value));
struct avl_node_t *find_max(struct avl_node_t *root);
int height(struct avl_node_t *root);
int max(int a, int b);
void inorder(struct avl_node_t *root, void (*uprint)(void *a, void *b));
void preorder(struct avl_node_t *root, void (*uprint)(void *a, void *b));
void postorder(struct avl_node_t *root, void (*uprint)(void *a, void *b));
void free_tree(struct avl_node_t *root, void (*ufree)(void *key, void *value));
void *find_key(struct avl_node_t *root, void *key, int (*ucmp)(void *a, void *b));

int max(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}

/**
 * Determines the height of the avl node.
 * @param root the root of the function
 * @return -1 if root is null, root->height otherwise
 */
int height(struct avl_node_t *root)
{
	if (!root)
		return -1;

	else
		return root->height;
}

/**
 * Creates a new AVL_T structure for the user
 * @return a opaque pointer to the new AVL_T structure
 */
T avl_new(void) 
{
	T avl = malloc(sizeof(struct T));
	assert(avl);
	avl->head = NULL;
	avl->count = 0;
	return avl;
}

/**
 * Inserts a new node into the avl tree.  Will rebalance the tree after insertion if needed
 * @param avl the AVL_T structure to add the node to
 * @param key the key to sort the node by
 * @param value the value associated with the key
 * @param ucmp the user provided comparison function to compare keys
 */
void avl_insert(T avl, void *key, void *value, int(*ucmp)(void *a, void *b)) 
{
	assert(avl);
	avl->head = insert(avl->head, key, value, ucmp);
	avl->count++;
}

/**
 * Rotates the nodes on an AVL tree left once
 * @param w the initial root node
 * @return the new root node
 */
struct avl_node_t *single_rotate_left(struct avl_node_t *x)
{
	struct avl_node_t *w = x->left;
	x->left = w->right;
	w->right = x;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	w->height = max(height(w->left), x->height) + 1;
	return w; 		/* new root */
	
}


/**
 * Rotates the nodes on an AVL tree right once
 * @param w the initial root node
 * @return the new root node
 */
struct avl_node_t *single_rotate_right(struct avl_node_t *w)
{
	struct avl_node_t *x = w->right;
	w->right = x->left;
	x->left = w;
	
	w->height = max(height(w->left), height(w->right)) + 1;
	x->height = max(height(x->right), w->height) + 1;
	return x; 		/* new root */
	
}

/**
 * Rotates the nodes on an AVL tree left twice
 * @param w the initial root node
 * @return the new root node
 */
struct avl_node_t *double_rotate_left(struct avl_node_t *z)
{
	z->left = single_rotate_right(z->left);
	return single_rotate_left(z);
}

/**
 * Rotates the nodes on an AVL tree right twice
 * @param w the initial root node
 * @return the new root node
 */
struct avl_node_t *double_rotate_right(struct avl_node_t *z)
{
	z->right = single_rotate_left(z->right);
	return single_rotate_right(z);
}

/**
 * Helper function of avl_insert.  Inserts the node, balances and determines the new height of the node
 * @param root the root node of the (sub)tree
 * @param key the key of the value to be inserted
 * @param value the value to be inserted
 * @param ucmp the user provided comparision function
 * @return the new root node of the (sub)tree
 */
struct avl_node_t *insert(struct avl_node_t *root, void *key, void *value, int (*ucmp)(void *a, void *b))
{
	int comp;

	if (!root) {
		root = malloc(sizeof(struct avl_node_t));
		assert(root);		
		root->key = key;
		root->value = value;
		root->height = 0;
		root->left = NULL;
		root->right = NULL;
		
		
	}
	comp = (*ucmp)(key, root->key);
	if(comp < 0) { /* left subtree */
		root->left = insert(root->left, key, value, ucmp);
		if ((height(root->left) - height(root->right)) == 2) {
			if ((*ucmp)(key, root->left->key) < 0) /* left subtree */
				root = single_rotate_left(root); /* LL */
			else 	/* LR */
				root = double_rotate_left(root);

		}
	}
	else if (comp > 0) { /* right subtree */
		root->right = insert(root->right, key, value, ucmp);
		if ((height(root->right) - height(root->left)) == 2) {
			if ((*ucmp)(key, root->right->key) < 0) /* left subtree */
				root = double_rotate_right(root); /* RL */
			else 	/* RR */
				root = single_rotate_right(root);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;

	return root;
}

/**
 * Deletes a node with a specified key value from the tree.  Rebalances and adjusts the heights of the
 * nodes accordingly
 * @param avl the avl tree to delete from
 * @param key the key value to delete from the tree
 * @param ucmp the user provided comparison function
 * @param ufree the user provided free function
 * @return None
 */
void avl_delete(T avl, void *key, int (*ucmp)(void *a, void *b), void (*ufree)(void *key, void *value)) 
{
	if (avl->count == 0) {
		printf("No nodes to AVL tree; nothing to delete.\n");
		return;
	}

	assert(avl);
	avl->head = delete_node(avl->head, key, ucmp, ufree);
	avl->count--;
}

/**
 * Deletes a node from a AVL tree, and then rebalances the tree
 * @param root the root of the tree to delete from
 * @param key the key to look for to delete
 * @param ucmp the user provided comparision functions
 * @param ufree the user provided free function
 * @return the pointer to the root of the avl tree
 */
struct avl_node_t *delete_node(struct avl_node_t *root, void *key, int (*ucmp)(void *a, void *b), void (*ufree)(void *key, void *value))
{
	struct avl_node_t *tmp, swap;
	int comp = 0;
	if (root != NULL) {
		comp = (*ucmp)(key, root->key);
	}

	/* find node */
	if (root == NULL)
		printf("element not found\n");
	else if(comp < 0) { /* left subtree */
		root->left = delete_node(root->left, key, ucmp, ufree);		
	}
	else if (comp > 0) { /* right subtree */
		root->right = delete_node(root->right, key, ucmp, ufree);		
	}
	else { 			/* found element */
		if (root->left && root->right) { /* two children */
			/* replace with largest in left subtree */		
			tmp = find_max(root->left);			
			/* copy the key and void pointers, not entire data */
			swap.key = root->key;
			swap.value = root->value;
			root->key = tmp->key;
			root->value = tmp->value;
			tmp->key = swap.key;
			tmp->value = swap.value; 
			root->left = delete_node(root->left, tmp->key, ucmp, ufree);			
		}
		else {
			tmp = root;
			/* no children */
			if (root->left == NULL && root->right == NULL)
				root = NULL;
			else if (root->left != NULL) 			/* one child */
				root = root->left;
			else
				root = root->right;

                        ufree(tmp->key, tmp->value);
                        free(tmp);
		}
	}	

	if (root != NULL && abs(height(root->left) - height(root->right)) == 2) { /* if unbalanced */
		if (height(root->left) > height(root->right)) {
			if (height(root->left->left) > height(root->left->right)) /* left side larger than right */
				root = single_rotate_left(root); /* striaght line */
			else 
				root = double_rotate_left(root); /* "dog leg" */
		} else /*same idea as above */
			if (height(root->right->right) > height(root->right->left))
				root = single_rotate_right(root);
			else
				root = double_rotate_right(root);

	}
	if (root) {
		root->height = max(height(root->left), height(root->right)) + 1;
	}	

	return root;
}

/**
 * Finds the maximum node of a given subtree
 * @param root the root of the (sub)tree to find the maxiumum child of
 * @return a pointer to the maximum node
 */
struct avl_node_t *find_max(struct avl_node_t *root)
{ // Make recursive function.  Upon a root->right failure, copy root to tmp, set root to null, return tmp
	//struct avl_node_t prev = NULL;
	while (root->right) {
		//prev = root;
		root = root->right;
	}
	//if (root->left) {
	//	prev->right = 
	//}
	return root;
}

/**
 * Prints the key and values of each avl node using the user provided print 
 * function inorder.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void avl_inorder(T avl, void (*uprint)(void *a, void *b))
{
        inorder(avl->head, uprint);
}

/**
 * Recursive helper function for avl_inorder that contains all the logic.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void inorder(struct avl_node_t *root, void (*uprint)(void *a, void *b))
{
        if (root != NULL) {
                inorder(root->left, uprint);
                (*uprint)(root->key, root->value);
                inorder(root->right, uprint);
        }
        
}

/**
 * Prints the key and values of each avl node using the user provided print 
 * function preorder.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void avl_preorder(T avl, void (*uprint)(void *a, void *b))
{
        preorder(avl->head, uprint);
}

/**
 * Recursive helper function for avl_preorder that contains all the logic.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void preorder(struct avl_node_t *root, void (*uprint)(void *a, void *b))
{
        if (root != NULL) {
                (*uprint)(root->key, root->value);
                preorder(root->left, uprint);
                preorder(root->right, uprint);
        }
        
}

/**
 * Prints the key and values of each avl node using the user provided print 
 * function postorder.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void avl_postorder(T avl, void (*uprint)(void *a, void *b))
{
        postorder(avl->head, uprint);
}

/**
 * Recursive helper function for avl_postorder that contains all the logic.
 * @param avl the avl structure with the tree to be printed
 * @param uprint the user provided print function
 */
void postorder(struct avl_node_t *root, void (*uprint)(void *a, void *b))
{
        if (root != NULL) {              
                postorder(root->left, uprint);
                postorder(root->right, uprint);
                (*uprint)(root->key, root->value);
        }
        
}

/**
 * Frees an avl structure and all of its contents.
 * @param avl the avl structure to free
 * @param ufree the user provided free function
 */
void avl_free(T avl, void (*ufree)(void *key, void *value)) 
{
	free_tree(avl->head, ufree);
	free(avl);
}

/**
 * Frees a binary tree.
 * @param root the root of the tree to free
 * @param the user provided free function.
 */
void free_tree(struct avl_node_t *root, void (*ufree)(void *key, void *value))
{
	if (root != NULL) {
		free_tree(root->left, ufree);
		free_tree(root->right, ufree);
		ufree(root->key, root->value);
		free(root);
	}
}

/**
 * Searches through a avl structure for a specified key, and returns a pointer 
 * to its value.
 * @param root the root of the tree to search.
 * @param key the key to search for
 * @param ucmp the user comparision function
 * @return The pointer to the value if found, null if not
 */
void *avl_find(T avl, void *key, int (*ucmp)(void *a, void *b))
{
        void *value = NULL;
        value = find_key(avl->head, key, ucmp);
        return value;
}

/**
 * Helper function for avl_find.  Gives the value associated with the key
 * @param root the root of the tree to search.
 * @param key the key to search for
 * @param ucmp the user comparision function
 * @return The pointer to the value if found, null if not
 */
void *find_key(struct avl_node_t *root, void *key, int (*ucmp)(void *a, void *b))
{
	void *value = NULL;
	int comp;
	if (root == NULL) {
		return NULL;
	}

	comp = ucmp(key, root->key);
	if (comp < 0) {
		value = find_key(root->left, key, ucmp);
	} else if (comp > 0) {
		value = find_key(root->right, key, ucmp);
	} else {
		value = root->value;
	}
	return value;
}
