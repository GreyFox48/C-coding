/**
 * @file dllist.h
 * @brief Header file for dllist.c.
 * @details See dllist.c for implementation details.
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#ifndef DLLIST_H_
#define DLLIST_H_

struct bit_t {
        unsigned int x;
        struct bit_t *next;
        struct bit_t *prev;
};

struct bit_t *create_node(int x);
void insert_head(struct bit_t **head, struct bit_t **tail, struct bit_t *node);
void insert_tail(struct bit_t **head, struct bit_t **tail, struct bit_t *node);
void insert_middle(struct bit_t **head, struct bit_t **tail, int pos, struct bit_t *node);
int count_nodes(struct bit_t *head);
void delete_list(struct bit_t **head, struct bit_t **tail);
void print_list(struct bit_t *head);

#endif
