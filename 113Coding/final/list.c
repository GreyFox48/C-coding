#include <stdio.h>
#include <stdlib.h>

struct node_t {
	int data;
	struct node_t * next;
};

struct node_t * create_node(int n) {
	struct node_t * node = malloc(sizeof(struct node_t));
	node->next = node;
	node->data = n;
	return node;
}

struct node_t * insert_head(struct node_t * head, struct node_t * node) {
	if (head == NULL)
		return node;
	head = node;
	node -> next = head;
	return head;
}

void print_list(struct node_t * head) {
	struct node_t * tmp = NULL;
	while (head != NULL) {
		tmp = head -> next;
		printf("%d", head -> data);
		if(tmp != NULL)
			printf("\t");
		else
			printf("\n");
		head = tmp;
	}
}


void delete_list(struct node_t * head) {
	struct node_t * tmp = NULL;
	while (head != NULL) {
		tmp = head -> next;
		free(head);
		head = tmp;
	}
}

int find_mid(struct node_t * head) {
	//change this to find the middle element.
	return 10;
}

struct node_t * delete_duplicates(struct node_t * head) {
	//change this to remove all duplicates
	return head;
}


int main(void) {
	struct node_t * head1;
	struct node_t * head2;
	int arr1[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
	int arr2[] = {1, 2, 8, 3, 5, 1, 3, 5, 7, 9};
	int i = 0;

	head1 = NULL;
	head2 = NULL;

	for (i = 0; i < sizeof(arr1)/sizeof(int); i ++)
		head1 = insert_head(head1, create_node(arr1[i]));

	for (i = 0; i < sizeof(arr2)/sizeof(int); i ++);
		head2 = insert_head(head2, create_node(arr2[i]));


	i = find_mid(head1);
	printf("The middle element of the first list is: %d\n", i);
	i = find_mid(head2);
	printf("The middle element of the second list is: %d\n", i);

	head1 = delete_duplicates(head1);
	print_list(head1);

	head2 = delete_duplicates(head2);
	print_list(head2);

	delete_list(head1);
	delete_list(head2);

	return 0;
}
