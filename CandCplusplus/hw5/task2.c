// Alternate program to fig12_03.c (Inserting and deleting nodes in a list)
/*
Name:Marco Salazar
Date: 2/28/18
Class: CS271 lab5 Task2
Only the insert and delete functions were changed as the instructions
	asked.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
   char data;
   struct listNode *nextPtr;
} ListNode;

typedef ListNode *ListNodePtr;

unsigned int getChoice() {
   unsigned int choice;
   puts("Enter your choice:\n"
        "   1 to insert an element into the list.\n"
        "   2 to delete an element from the list.\n"
        "   3 to end.");
   printf("%s", "? ");
   scanf("%u", &choice);
   return choice;
}

// insert a new value into the list in sorted order
//this is the rewritten code for Task 2
void insert(ListNodePtr *sPtr, char value)
{
	if(*sPtr && (*sPtr)->data < value){
		sPtr = &((*sPtr)->nextPtr);
		insert(sPtr, value);
	}
	else{
	ListNodePtr newPtr = malloc(sizeof(ListNode));
	if(!newPtr) {printf("%c not inserted. No memory available.\n",value); return;}
	newPtr->data = value;
	newPtr->nextPtr = *sPtr;
	*sPtr = newPtr;
	}
}

// delete a list element
//this is the Rewritten code for Task 2
char delete(ListNodePtr *sPtr, char value)
{
   if(*sPtr && (*sPtr)->data < value){
	   sPtr = &((*sPtr)->nextPtr);
	   return delete(sPtr, value);
   }
   else{
    	if (!(*sPtr) || value != (*sPtr)->data) return '\0'; // 'value' not found in list
    	ListNodePtr tempPtr = *sPtr;                         // hold onto node being removed
    	*sPtr = (*sPtr)->nextPtr;                            // de-thread the node
    	free(tempPtr);                                       // free the de-threaded node
		return value;
	}
}

void printList(ListNodePtr currentPtr)
{
   puts("The list is:");
   for (; currentPtr; currentPtr = currentPtr->nextPtr) printf("%c --> ", currentPtr->data);
   puts("NULL\n");
}

int main(void)
{
   ListNodePtr startPtr = NULL;
   char item;

   while (1)
      switch (getChoice()) {
         case 1:
            printf("%s", "Enter a character: ");
            scanf("\n%c", &item);
            insert(&startPtr, item);
            printList(startPtr);
            break;
         case 2: // delete an element
            printf("%s", "Enter character to be deleted: ");
            scanf("\n%c", &item);
            if (!startPtr)                {puts("List is empty.\n");          break;}
            if (!delete(&startPtr, item)) {printf("%c not found.\n\n", item); break;}
            printf("%c deleted.\n", item);
            printList(startPtr);
            break;
         case 3:
            puts("End of run.");
            return;
         default:
            puts("Invalid choice.\n");
            break;
      } // end switch
}