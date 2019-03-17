/**
 * @file dllist.c
 * @brief Library for a doubly linked list.  Most functions are for my later
 * use and not for lab 9.
 * @details Allows the creation of a doubly linked list.  Allows addition at the
 * head, tail, and middle, as well as node removal, list deletion, and counting
 * the nodes.  Most functions must be given both a head and tail pointer to a
 * pointer.
 *
 * @author Matthew Olsen
 * @date November 16, 2015
 * @todo Nothing
 * @bug none
 */

#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#define NODE_FAILURE 13

/**
 * creates a node structure by allocating memory
 * @param x the value to be stored in the node
 * @return the address of the created node
 */
struct bit_t *create_node(int x) {
        struct bit_t *node = malloc(sizeof(struct bit_t));
        if (!node) {
                printf("Node in dllist.c failed to allocate properly.\n");
                exit(NODE_FAILURE);
        }

        node->next = NULL;
        node->prev = NULL;
        node->x = x;

        return node;
}

/**
 * inserts a node at the head of the doubly linked list, and reassigns the head
 * pointer and possibly the tail
 * @param head the head of the list to add to
 * @param tail the tail of the list to add to
 * @param node the node to add to the given list
 */
void insert_head(struct bit_t **head, struct bit_t **tail, struct bit_t *node){

        if(!(*head) && !(*tail)) { /* accounts for if the list is empty */
                *head = node;
                *tail = node;
                return;
        }

        node->next = *head;
        (*head)->prev = node;
        *head = node;
}

/**
 * inserts a node at the tail end of a list, reassinging tail and maybe head
 * @param head the head of the list
 * @param tail the tail of the list
 * @param node the node to be added to the tail of the list
 */
void insert_tail(struct bit_t **head, struct bit_t **tail, struct bit_t *node) {

        if (!(*head) && !(*tail)) { /* accounts for if list is empty */
                *head = node;
                *tail = node;
                return;
        }

        node->prev = *tail;
        (*tail)->next = node;
        *tail = node;
}

/**
 * Inserts a node into the middle of the list, based on given position.  The
 * inserted node will replace the position of the previous node at said position
 * while demoting the old nodes downwards in the list order.  The list order
 * is based upon 1 indexing
 * @param head the head of the list
 * @param tail the tail of the list
 * @param pos the position in the list to insert the node at
 * @param node the node of the list
 */
void insert_middle(struct bit_t **head, struct bit_t **tail, int pos, struct bit_t *node) {
        int i = 1;
        struct bit_t *temp = *head;

        if (pos <= 1) { /* accounts for errors and an easy case */
                insert_head(head, tail, node);
                return;
        } else if (pos > count_nodes(*head)) { /* same as previous if statement*/
                insert_tail(head, tail, node);
                return;
        }

        for ( ; temp && (i < pos); temp = temp->next, i++) {
                ; /*find the position in the list */
        }

        node->prev = temp->prev;
        temp->prev->next = node;
        node->next = temp;
        temp->prev = node;

}

/**
 * counts the number of nodes that are present in the doubly linked list
 * @param head the head of the list
 * @return the number of nodes in the list
 */
int count_nodes(struct bit_t *head) {
        int count = 0;
        for ( ; head; head = head->next) {
                count++;
        }
        return count;
}

/**
 * frees all the nodes in a given list, and sets head and tail pointers equal
 * to NULL
 * @param head the head of the list
 * @param tail the tail of the list
 */
void delete_list(struct bit_t **head, struct bit_t **tail) {
        struct bit_t *delete = NULL;
        while (*head){
                delete = *head;
                *head = (*head)->next;
                free(delete);
        }
        *head = NULL;
        *tail = NULL;
}

/**
 * prints the contents of each node, starting at the head
 * @param head the head of the list
 */
void print_list(struct bit_t *head) {
        while (head) {
                printf("Node: %p\t", head);
                printf("Prev: %p\t", head->prev);
                printf("x: %u\t", head->x);
                printf("Next: %p\n", head->next);
                head = head->next;
        }
}
