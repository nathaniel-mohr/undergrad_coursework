/*
 * Program Filename: list.c
 * Author: Nathaniel Mohr
 * Date: June 10, 2018
 * Description: Collection of functions that are related to singly linked lists
 * Input: 
 * Output:
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Function: length
 * Description: finds the length of a linked list
 * Parameters: struct node*
 * Pre-Conditions: none
 * Post-Conditions: accurate length of list
 */
int length(struct node* head){
	int counter = 0;
	struct node* curr = head;
	while(curr != NULL){
		counter++;
		curr = curr->next;
	}
	return counter;
}

/*
 * Function: print
 * Description: prints a linked list
 * Parameters: struct node*, int
 * Pre-Conditions: num is less than the length of the linked list
 * Post-Conditions: list is printed
 */
void print(struct node* head, int num){
	int counter = 0;
	struct node* curr = head;
	while(counter < num){
		printf("%d ", curr->val);
		curr = curr->next;
		counter++;
	}
	printf("\n");
}

/*
 * Function: push
 * Description: adds a node to the beginning of a linked list
 * Parameters: struct node*, int
 * Pre-Conditions: none
 * Post-Conditions: node has been added to the beginning of a linked list
 */
struct node* push(struct node* head, int set_val){
	struct node* temp = (struct node*)(malloc(sizeof(struct node)));
	temp->val = set_val;
	temp->next = head;
	head = temp;
	return head;
}

/*
 * Function: append
 * Description: adds a node to the end of a linked list
 * Parameters: struct node*, int
 * Pre-Conditions: none
 * Post-Conditions: node has been added to the end of a linked list
 */
struct node* append(struct node* head, int set_val){
	int i;
	int list_length;
	struct node* curr = head;
	struct node* temp = (struct node*)(malloc(sizeof(struct node)));
	temp->val = set_val;
	temp->next = NULL;
	if(head == NULL){
		head = temp;
		return head;
	}
	list_length = length(head);
	for(i = 0; i < list_length - 1; i++){
		curr = curr->next;
	}
	curr->next = temp;
	return head;
}

/*
 * Function: clear
 * Description: clears a linked list
 * Parameters: struct node*
 * Pre-Conditions: none
 * Post-Conditions: list is empty and no memory leaks
 */
struct node* clear(struct node* head){
	int i;
	struct node* curr = head;
	struct node* temp;
	for(i = 0; i < length(head); i++){
		temp = curr->next;
		free(curr);
		curr = temp;	
	}
	head = NULL;
	return head;
}

/*
 * Function: remove_node
 * Description: removes a node from a linked list
 * Parameters: struct node*, int
 * Pre-Conditions: index is less than the length of the list
 * Post-Conditions: node has been removed
 */
struct node* remove_node(struct node* head, int index){
	int i;
	struct node* curr = head;
	struct node* temp;
	for(i = 0; i < index - 1; i++){
		curr = curr->next;
	}
	temp = curr->next->next;
	free(curr->next);
	curr->next = temp;
	return head;
}

/*
 * Function: sort_ascending
 * Description: sorts the list in ascending order
 * Parameters: struct node*
 * Pre-Conditions: none
 * Post-Conditions: list has been sorted
 */
struct node* sort_ascending(struct node* head){
	int i, j;
	struct node* curr = head;
	struct node* temp;
	int list_length = length(head);
	for(i = 1; i < list_length; i++){
		for(j = 0; j < list_length - i; j++){
			if(curr->val < curr->next->val){
				//swaps nodes			
			}
			curr = curr->next;
		}
		curr = head;
	}
	return head;
}

/*
 * Function: sort_descending
 * Description: sorts the list in descending order
 * Parameters: struct node*
 * Pre-Conditions: none
 * Post-Conditions: list has been sorted
 */
struct node* sort_descending(struct node* head){
	int i, j;
	struct node* curr = head;
	struct node* temp;
	int list_length = length(head);
	for(i = 1; i < list_length; i++){
		for(j = 0; j < list_length - i; j++){
			if(curr->val < curr->next->val){
				//swaps nodes			
			}
			curr = curr->next;
		}
		curr = head;
	}
	return head;
}

/*
 * Function: insert_middle
 * Description: inserts a node into a specefic position in a linked list
 * Parameters: struct node*, int, int
 * Pre-Conditions: pos is less than the length of the list
 * Post-Conditions: node has been added to the list
 */
struct node* insert_middle(struct node* head, int set_val, int pos){
	int i;
	struct node* curr;
	struct node* add = (struct node*)malloc(sizeof(struct node));
	temp->val = set_val;
	if(pos == 0){
		head = add;
		add->next = curr;
	}else{
		for(i = 0; i < pos - 1; i++){
			curr = curr->next;
		}
		add->next = curr->next;
		curr->next = add;
	}
	return head;
}
