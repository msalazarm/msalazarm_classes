// Fig. 12.19: fig12_19.c
// Creating and traversing a binary tree
// preorder, inorder, and postorder
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// self-referential structure
struct treeNode {
   struct treeNode *leftPtr; // pointer to left subtree
   int data; // node value
   struct treeNode *rightPtr; // pointer to right subtree
};

typedef struct treeNode TreeNode; // synonym for struct treeNode
typedef TreeNode *TreeNodePtr; // synonym for TreeNode*

// prototypes
void insertNode(TreeNodePtr &treePtr, int value);
void print(TreeNodePtr rootPtr);

// function main begins program execution
int main(void)
{
   TreeNodePtr rootPtr = NULL; // tree initially empty

   srand(time(NULL));
   cout << "The numbers being placed in the tree are:" << endl;

   // insert random values between 0 and 14 in the tree
   int i;
   for (i = 1; i <= 15; ++i) {
      int item = rand() % 20;
      cout << "insert " << item << endl;
      insertNode(rootPtr, item);
      cout << endl;
      print(rootPtr);
   }

}

// insert node into tree
void insertNode(TreeNodePtr &treePtr, int value)
{
   // if tree is empty
   if (treePtr == NULL) {
      treePtr = (TreeNodePtr) malloc(sizeof(TreeNode));

      // if memory was allocated, then assign data
      if (treePtr != NULL) {
         (treePtr)->data = value;
         (treePtr)->leftPtr = NULL;
         (treePtr)->rightPtr = NULL;
      }
      else {
		  cout << value << "%d not inserted. No memory available." << endl;
      }
   }
   else { // tree is not empty
      // data to insert is less than data in current node
      if (value < (treePtr)->data) {
         insertNode((treePtr->leftPtr), value);
      }

      // data to insert is greater than data in current node
      else if (value > (treePtr)->data) {
         insertNode((treePtr->rightPtr), value);
      }
      else { // duplicate data value ignored
      	cout << "  (duplicate)";
      }
   }
}

void printHelper(TreeNodePtr treePtr, int depth)
{
   int i;
   if (treePtr == NULL) return;
   printHelper(treePtr->rightPtr, depth+1);
   for (i=0; i<depth; i++) cout << "   ";
   cout << treePtr->data << endl;
   printHelper(treePtr->leftPtr,  depth+1);
}

void print(TreeNodePtr rootPtr) {
	cout << endl;
   printHelper( rootPtr, 0 );
   cout << endl;
}


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
