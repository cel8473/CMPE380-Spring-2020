/******************************************************************************
 An student framework implementation of doubly linked lists that holds 
 elements containing a 256 character string and a sequence number.
 12/24/2017 - R. Repka     Removed AddToFrontOfLinkedList()
 03/12/2018 - R. Repka     Added pseudo code 
 09/17/2019 - R. Repka     fixed minor prototype errors 
 09/26/2019 - R. Repka     Added comments to RemoveFromFrontOfLinkedList()
 10/01/2019 - R. Repka     Changed search function to int
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "LinkedLists.h"


/******************************************************************************
  Pseudo code: 
  
  add 1st node
    LinkedList front = points to node 1,  LinkedList back = points to node 1
      Node 1 next     = NULL  (at the end)
      Node 1 previous = NULL (at the start)
          
  add 2nd node
    LinkedList front = points to node 1,  LinkedList back = points to node 2
      Node 1 next points to node 2             Node 2 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)    Node 2 previous points to node 1

  add 3rd node
  LinkedList front = points to node 1,  LinkedList back = points to node 3
      Node 1 next points to node 2           Node 2 next points to node 3      Node 3 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)  Node 2 previous points to node 1  Node 3 previous points to node 2
      
   Note: It is possible to implement with only 2 special cases 
      
   Remove from front of 3 node list 
    save the pointer to the data and return it at the end
    LinkedList front = points to node 2,  LinkedList back = points to node 3
      Node 2 next points to node 3           Node 3 next   = NULL  (at the end)
      Node 2 previous = NULL (at the start)  Node 3 previous points to node 2
      free Node but NOT the data
******************************************************************************/

/******************************************************************************
 Initialize the linked list data structure.  Points to nothing, no entries.

 Where: LinkedLists *ListPtr - Pointer to the linked list to create
 Returns: nothing
 Errors: none
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr)
{
	ListPtr->NumElements = 0;
	ListPtr->FrontPtr = NULL;
	ListPtr->BackPtr = NULL;
} /* InitLinkedList() */


/******************************************************************************
 Adds a node to the back of the list.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to add to
        char *DataPtr - Pointer to the data to add to the list
 Returns: nothing
 Errors: Prints to stderr and exits
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, char *DataPtr)
{
	LinkedListNodes *newback = (LinkedListNodes *) malloc(sizeof(LinkedListNodes));
	if(newback == NULL){
		fprintf(stderr, "Malloc was unsuccessful, AddToBackOfLinkedList()");
		exit(-99);
	}
	newback->Next = NULL;
	memcpy(newback->String, DataPtr, MAX_BUFF_LEN-1);
	if(ListPtr->BackPtr != NULL){		
		newback->Previous = ListPtr->BackPtr;
		ListPtr->BackPtr->Next = newback;
		ListPtr->BackPtr = newback;
	}
	else{
		newback->Previous = NULL;
		ListPtr->FrontPtr = newback;
		ListPtr->BackPtr = newback;
	}
	ListPtr->NumElements++;
} /* AddToBackOfLinkedList */

/******************************************************************************
 Removes a node from the front of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.  
 Note: This you will need to malloc a string buffer and copy the data from the
       linked list node before destroying the node.  The calling routine was
       written to free the string so there are no memory leaks

 
   Linked lists contain nodes, which contain data strings
 
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the data removed or NULL for none
 Errors: none
******************************************************************************/
char *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr)
{
	char *string = malloc(MAX_BUFF_LEN);
	if(ListPtr->NumElements == 0) {
		return NULL;
	}
	else if(ListPtr->NumElements == 1){
		strncpy(string, ListPtr->FrontPtr->String, MAX_BUFF_LEN);
		free(ListPtr->FrontPtr);
		ListPtr->FrontPtr = NULL;
		ListPtr->BackPtr = NULL;
	}
	else if(ListPtr->NumElements > 1){
		strncpy(string, ListPtr->FrontPtr->String, MAX_BUFF_LEN);
		ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
		free(ListPtr->FrontPtr->Previous);
		ListPtr->FrontPtr->Previous = NULL;
	};
	ListPtr->NumElements--;
	return string;
} /* RemoveFromFrontOfLinkedList() */


/******************************************************************************
 De-allocates the linked list and resets the struct fields (in the header) 
 to indicate that the list is empty.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to destroy
 Returns: nothing
 Errors: none
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr)
{
	while(ListPtr->NumElements>0){
		char *string = RemoveFromFrontOfLinkedList(ListPtr);
		free(string);
	};
	ListPtr = NULL;
} /* DestroyLinkedList() */


/******************************************************************************
 Searches the linked list for a provided word. If found, returns the pointer
 to the element struct. If not found, returns a NULL pointer
 
 Where: LinkedLists *ListPtr - Pointer to the linked list to search
        char *String         - Pointer to the string to search
 Returns: 1 if found, 0 otherwise
 Errors: none
 * ***************************************************************************/
int SearchList(LinkedLists *ListPtr, char *String)
{
/*-----  Don't implement this until instructed in Lab 6 ----*/
return 0;
} /* SearchList() */

