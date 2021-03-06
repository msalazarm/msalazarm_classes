// Fig. 12.19: fig12_19.c
// Creating and traversing a binary tree
// preorder, inorder, and postorder

/*
Name: Marco Salazar
Date: 2/26/18
Aggie ID: 800644244
Class: CS271 lab5 Task3
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// self-referential structure
typedef struct treeNode {
	struct treeNode *subtree[2];//subtree[0] is left subtree; subtree[1] is right subtree
	int data;                   //node value
} TreeNode;
/*
struct treeNode {
   struct treeNode *leftPtr; // pointer to left subtree
   int data; // node value
   struct treeNode *rightPtr; // pointer to right subtree
};*/

typedef TreeNode* TreeNodePtr;

// prototypes
void insertNode(TreeNodePtr *treePtr, int value);
void print(TreeNodePtr p);

// function main begins program execution
int main(void)
{
   TreeNodePtr rootPtr = NULL; // tree initially empty

   srand(time(NULL));
   puts("The numbers being placed in the tree are:");

   // insert random values between 0 and 14 in the tree
   for (unsigned int i = 1; i <= 10; ++i) {
      int item = rand() % 15;
      printf("%3d", item);
      insertNode(&rootPtr, item);
      print(rootPtr);
   }
}

// insert node into tree
void insertNode(TreeNodePtr *treePtr, int value)
{
   for(; *treePtr; treePtr = &((*treePtr)->subtree[ value > ((*treePtr)->data) ]) );
      *treePtr = malloc(sizeof(TreeNode));

      // if memory was allocated, then assign data
      if (*treePtr != NULL) {
         (*treePtr)->data = value;
         (*treePtr)->subtree[0] = NULL;
         (*treePtr)->subtree[1] = NULL;
      }
      else {
         printf("%d not inserted. No memory available.\n", value);
      }
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