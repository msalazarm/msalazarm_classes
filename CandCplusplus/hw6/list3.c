// list3.c
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
 while (p->ptr)
 p = p->ptr;
 p->ptr = NewListNode( n );
}
void printList( pointer p ) {
 for (;p;p=p->ptr) printf("%d\n", p->data);
}
main() {
 pointer head = NULL;
 insertAtTheEnd( head, 5 );
 insertAtTheEnd( head, 7 );
 insertAtTheEnd( head, 2 );
 insertAtTheEnd( head, 4 );
 printList( head );
}
