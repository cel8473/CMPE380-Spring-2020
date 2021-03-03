/****************************************************************************
 The purpose of this example is to exercise, using pointers
 
 student version 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_c.c -o lab_c
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_c
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
  These data structures are used to simulated a very simple linked list
---------------------------------------------------------------------------*/
typedef struct Node{
    int index;   	//Index of the array   
    struct Node *next;  //The next node
    char string[40];	//Array of chars that the node stores
} Node;

typedef struct {
    int nterms;      	//How many nodes there are.
    Node *front;       	//The front node
} Wrapper;



// Function prototypes
void printList(Wrapper *wrapper_p);

int main(int argc, char *argv[]) {
   Wrapper *wrapper_p;
   Node *node_p;
   Node *temp_p;
 
   // Wire the first node in 
   wrapper_p = (Wrapper *) malloc(sizeof(Wrapper)); 
   node_p = (Node *) malloc(sizeof(Node));
   if(wrapper_p == NULL){
	printf("Malloc failed for wrapper_p");
	exit(-99);
   }
   if(node_p == NULL){
	printf("Malloc failed for node_p");
	exit(-99);
   }
   node_p->index = 1;
   node_p->next = NULL;
   strncpy(node_p->string, "one", 39); 
   wrapper_p->front = node_p;
   wrapper_p->nterms = 1;
   printList(wrapper_p);
 
   // Wire the second node in   
   temp_p =(Node *) malloc(sizeof(Node)); 
   if(temp_p == NULL){
	printf("Malloc failed for temp_p");
	exit(-99);
   }
   temp_p->index = 2;
   temp_p->next = NULL;
   strncpy(temp_p->string, "two", 39);
   node_p->next = temp_p;
   wrapper_p->nterms = 2;
   printList(wrapper_p);
   
   // Clean up memory  
   free(node_p);
   free(temp_p);
   free(wrapper_p);
   wrapper_p = NULL;
   node_p = NULL;
   temp_p = NULL;
   printf("Clean up complete\n");
   return 0;
}

// Walk the linked list and print the contents 
void printList(Wrapper *wrapper_p) {
   Node *current = wrapper_p->front;
   printf("Printing a %d node linked list\n", wrapper_p->nterms);
   for(int i = 0; i < wrapper_p->nterms; i++){
	printf(" node %d contains the string '%s'\n", current->index, current->string);
	if(current->next != NULL){
		current = current->next;
	};
   }
}

