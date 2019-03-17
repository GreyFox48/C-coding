/**
 * @file lab8.c
 * @brief Stores user's inputed numbers via a linked list.
 * @details The program is able to store numbers at the beginning, middle, and
 * end of the list, find a number in the list, print the contents of the list,
 * count the number of nodes, delete a node with a specified value, and is also
 * able to free itself.
 *
 * @author Matthew Olsen
 * @date 2 Nov. 2015
 * @bug inputing a negative position for some functions will cause errors
 * @todo Implement user input checking
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MALLOC_FAILURE 13
#define BUFF 25

struct node_t {
        double x;
        struct node_t *next;
};

struct node_t *create_node(double n);
void print_node(struct node_t *node);
void print_list(struct node_t *head);
struct node_t *insert_head(struct node_t *head, struct node_t *node);
struct node_t *insert_tail(struct node_t *head, struct node_t *node);
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos);
int count_nodes(struct node_t *head);
struct node_t *find_node(struct node_t *head, double n);
struct node_t *delete_node(struct node_t *head, double n);
void delete_list(struct node_t *head);

int main(void)
{
        char input[BUFF];
        struct node_t *head = NULL;
        struct node_t *temp = NULL; /* used for return value of find_node */
        int option; /* what menu option the user chooses */
        double x;
        int pos; /* for insert_middle function */

        while (1) { /* program stops only by return under case statement */
                printf("What would you like to do?\n");
                printf("1. Enter a number.\n");
                printf("2. Delete a number.\n");
                printf("3. Print all numbers.\n");
                printf("4. Print number of items in a list.\n");
                printf("5. Find if a number is in the list.\n");
                printf("6. Quit program.\n");
                printf("Select number: ");
                fgets(input, BUFF, stdin);
                option = atoi(input);

                switch (option) {
                case 1: /* User inputs number */
                        printf("1. Enter a number at the head.\n");
                        printf("2. Enter a number in the middle.\n");
                        printf("3. Enter a number at the tail.\n");
                        printf("Select number: ");
                        fgets(input, BUFF, stdin);
                        option = atoi(input);

                        switch (option) {
                        case 1: /* User inputs number at head */
                                printf("Input x:");
                                fgets(input, BUFF, stdin);
                                x = atof(input);
                                head = insert_head(head, create_node(x));
                                break;
                        case 2: /* User inputs number in the middle */
                                printf("Input x:");
                                fgets(input, BUFF, stdin);
                                x = atof(input);
                                printf("Input pos:");
                                fgets(input, BUFF, stdin);
                                pos = atoi(input);
                                head = insert_middle(head, create_node(x), pos);
                                break;
                        case 3: /* User inputs number at tail */
                                printf("Input x:");
                                fgets(input, BUFF, stdin);
                                x = atof(input);
                                head = insert_tail(head, create_node(x));
                                break;
                        default: /* error catching */
                                printf("I do not understand %d.\n", option);
                        }

                        break; /* break for user input case */
                case 2: /* user deletes number */
                        printf("Input number to delete: ");
                        fgets(input, BUFF, stdin);
                        x = atof(input);
                        head = delete_node(head, x);
                        break;

                case 3: /* print the list */
                        print_list(head);
                        break;
                case 4: /* count the number of nodes */
                        printf("There are %d nodes.\n", count_nodes(head));
                        break;
                case 5: /* to find a node in the linked list */
                        printf("Find x:");
                        fgets(input, BUFF, stdin);
                        x = atof(input);
                        temp = find_node(head, x);
                        if (temp) {
                                printf("Found %lf at node %p.\n", x, temp);
                        } else {
                                printf("Did not find %lf in the list.\n", x);
                        }
                        break;
                case 6: /* exit the program and free allocated memory */
                        printf("Goodbye!\n");
                        delete_list(head);
                        return 0;
                default: /* error catching */
                        printf("I do not understand %d.\n", option);
                }
        }

}

/**
 * Allocates a structure of type node_t and assigns a double to its data field
 * and NULL for its pointer
 * @param n the double to be assigned to the structure's data field
 * @return the base address of the new node
 */
struct node_t *create_node(double n)
{
        struct node_t *node = malloc(sizeof(struct node_t));

        if (!node){
                printf("Malloc failure... Goodbye.\n");
                exit(MALLOC_FAILURE);
        }

        /*populate node */
        node->x = n;
        node->next = NULL;

        return node;
}

/**
 * Prints the address of a given node, as well as its double and the address
 * it points to itself
 * @param node the address of the node
 */
void print_node(struct node_t *node)
{
        printf("Address of node: %p\t", node);
        printf("x: %lf\t", node->x);
        if (node->next)
                printf("*next: %p\n", node->next);
        else
                printf("*next: NULL\n");
}

/**
 * Prints all of the contents of the linked list
 * @param head the head of the linked list
 */
void print_list(struct node_t *head)
{
        while (head) {
                print_node(head);
                puts(""); /* makes list a little easier to read in my opinion */
                head = head->next;
        }
}

/**
 * inserts new node at the head of the list
 * @param head the current head of the list
 * @param node the going-to-be head of the list
 */
struct node_t *insert_head(struct node_t *head, struct node_t *node)
{
        node->next = head;
        head = node;

        return head;
}

/**
 * insertes a new node at the tail end of the linked list
 * @param head the head address of the linked list
 * @param node the node to be added to the linked list
 * @return the address of the head of the list
 */
struct node_t *insert_tail(struct node_t *head, struct node_t *node)
{
        struct node_t *i = head;

        if (!head) { /* for case of creating first node in list */
                head = node;
                return head;
        }

        /* find when a next pointer == NULL */
        while(i->next) {
                i = i->next;
        }
        i->next =  node;

        return head;

}

/**
 * Inserts a node in middle of a linked list at a specified index position.
 * Note that indexing begins at one.  If the list is too short
 * for the specified position, attatches node to tail of the list.
 * @param head the head of the list
 * @param node the node to be inserted into the list
 * @param pos the posiiton in the list node is to be inserted at
 * @return the head of the list
 */
struct node_t *insert_middle(struct node_t *head, struct node_t *node, int pos)
{
        int i = 1; /* accounts for indexing starting at 1, prevents off by 1 */
        struct node_t *prev = NULL;
        struct node_t *temp = head; /* to help keep track of head */

        if (pos > count_nodes(head)) { /* if user pos is greater than list
                                        * length */
                head = insert_tail(head, node);
                return head;
        } else if (pos == 1) { /* special case needed to prevent error in
                                * upcoming for loop*/
                head = insert_head(head, node);
                return head;
        }

        while (i++ < pos) { /* increments prev and temp to desired addresses */
                prev = temp; /* prev will be node prior to desired position */
                temp = temp->next; /* temp will be node at said position */
        }

        /* insert node between temp and prev, */
        node->next = temp;
        prev->next = node;

        return head;
}

/**
 * count the nuber of nodes that exist
 * @param head the head of the list
 * @return the number of nodes in the list
 */
int count_nodes(struct node_t *head)
{
        int i = 0;

        while (head) { /* can simply use head here b/c no risk of segfault */
                i++;
                head = head->next;
        }

        return i;
}

/**
 * finds the first node containing a specified node in a linked list and returns
 * the address of the node
 * @param head the head of the linked list
 * @param n the double to find in the list
 * @return the address of node containing n
 */
struct node_t *find_node(struct node_t *head, double n)
{
        struct node_t *node = NULL;

        while (head) {
                /* if both cases are true then n and x must be equal */
                if (isgreaterequal(n, head->x) && islessequal(n, head->x)){
                        node = head;
                        break; /*no need to continue searching */
                }
                head = head->next;

        }

        return node;
}

/**
 * deletes the first node in the list containing containing a certain double
 * value
 * @param head the head of the list to searching
 * @param n the value to find in the list to delete the related node
 * @return the head of the list
 */
struct node_t *delete_node(struct node_t *head, double n)
{
        struct node_t *node = find_node(head, n);
        struct node_t *prev = NULL;
        struct node_t *temp = head; /*needed to prevent changing head's address
                                     * when unnecessary */

        if (node == head) { /*special case needed to handle changing of head */
                head = head->next;
                free(node);
                return head;
        } else if (!node) {
                printf("There is no %lf in the list.\n", n);
                return head;
        }

        while (temp->next) {
                prev = temp;
                temp = temp->next;
                if (temp == node) {
                        prev->next = temp->next;
                        free(temp);
                        break; /* no need to continue looking */
                }
        }

        return head;
}

/**
 * frees all allocated memory in the list, starting from the head
 * @param head the head of the list
 */
void delete_list(struct node_t *head)
{
        struct node_t *delete = NULL;

        while(head) {
                delete = head; /* keep track of head */
                head = head->next;
                free(delete);
        }
}
