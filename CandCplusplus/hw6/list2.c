// list2.c
#include <stdio.h>
#include <stdlib.h>
typedef struct listStruct *pointer;
typedef struct listStruct
{
 int data;
 pointer ptr;
} list;
pointer NewListNode( int n ) {
 pointer p;
 p = (pointer) malloc(sizeof(list));
 p->data = n;
 p->ptr = NULL;
 return p;
}
void insertAtTheEnd( pointer p, int n ) {
 if (p == NULL)
 {p = NewListNode( n );
 return;}
 insertAtTheEnd( p->ptr, n );
}
void printList( pointer p ) {
 if (p==NULL)
 return;
 printf("%d\n", p->data);
 printList( p->ptr);
}
main() {
 pointer head = NULL;
 // the first element is handled differently than the rest
 // of the insertions (which are handled by insertAtTheEnd
 head = NewListNode( 5 );
 insertAtTheEnd( head, 7 );
 insertAtTheEnd( head, 2 );
 insertAtTheEnd( head, 4 );
 printList( head );
}
