/**
 * @file avl.h
 * @brief Implements a avl tree.
 * @details See avl.c for implementation details.
 *
 * @date May 7, 2016
 * @author Matthew Olsen
 * @bugs None.
 * @todo Nothing
 */ 

#ifndef AVL_H_
#define AVL_H_

typedef struct AVL_T *AVL_T;

void avl_delete(AVL_T avl, void *key, int (*ucmp)(void *a, void *b), void (*ufree)(void *key, void *value));
void avl_insert(AVL_T avl, void *key, void *value, int(*ucmp)(void *a, void *b));
void avl_inorder(AVL_T avl, void (*uprint)(void *a, void *b));
void avl_preorder(AVL_T avl, void (*uprint)(void *a, void *b));
void avl_postorder(AVL_T avl, void (*uprint)(void *a, void *b));
AVL_T avl_new(void);
void avl_free(AVL_T avl, void (*ufree)(void *key, void *value));
void *avl_find(AVL_T avl, void *key, int (*ucmp)(void *a, void *b));

#endif
