#ifndef BST_H
#define BST_H


typedef struct BST_T *BST_T;

BST_T bst_new(void);

/* int (*ucmp)(void *, void *) user defined function for comparison of key */
int bst_insert(BST_T bst, void *key, void *data, int (*ucmp)(void *, void *));

/* *uprint is a user supplied function on how to print key and data f(key, data) */
void bst_inorder(BST_T bst, void (*uprint)(void *, void *));

#endif 
