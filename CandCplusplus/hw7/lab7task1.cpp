// Alternate program to fig12_03.c (Inserting and deleting nodes in a list)

#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct listNode {
   char data;
   struct listNode *nextPtr;
} ListNode;

typedef ListNode *ListNodePtr;

unsigned int getChoice() {
   unsigned int choice;
   cout << "Enter your choice:\n" <<
        "   1 to insert an element into the list.\n" <<
        "   2 to delete an element from the list.\n" <<
        "   3 to end." << endl;
   cout << "? " << endl;
   cin >> choice;
   return choice;
}

// insert a new value into the list in sorted order
void insert(ListNodePtr &sPtr, char value)
{
   if (!(sPtr) || (sPtr)->data >= value)
   {
      ListNodePtr newPtr = (ListNodePtr) malloc(sizeof(ListNode));
      if (!newPtr) {
		  cout << value << " not inserted. No memory available." << endl;}
      newPtr->data = value;
      newPtr->nextPtr = sPtr;
      sPtr = newPtr;
      return;
   }
   insert( (sPtr)->nextPtr, value );  // tail recursion
}

// delete a list element
char del(ListNodePtr &sPtr, char value)
{
   if (!(sPtr) || (sPtr)->data > value) return '\0';
   if ((sPtr)->data == value)
   {
      ListNodePtr tempPtr = sPtr;
      sPtr = (sPtr)->nextPtr;
      free(tempPtr);
      return value;
   }
   return del( (sPtr)->nextPtr, value );  // tail recursion
}

void printList(ListNodePtr currentPtr)
{
	cout << "The list is:" << endl;
   for (; currentPtr; currentPtr = currentPtr->nextPtr) cout << currentPtr->data << " --> ";
   cout << "NULL" << endl;
}

int main(void)
{
   ListNodePtr startPtr = NULL;
   char item;

   while (1)
      switch (getChoice()) {
         case 1:
         	cout << "Enter a character: " << endl;
         	cin >> item;
            insert(startPtr, item);
            printList(startPtr);
            break;
         case 2: // delete an element
         	cout << "Enter character to be deleted: " << endl;
         	cin >> item;
            if (!startPtr)                {cout << "List is empty. " << endl;          break;}
            if (!del(startPtr, item)) {cout << item << " not found. " << endl << endl; break;}
            cout << item << " deleted. " << endl;
            printList(startPtr);
            break;
         case 3:
         	cout << "End of run." << endl;
            return 0;
         default:
         	cout << "Invalid choice. " << endl;
            break;
      } // end switch
}
