/*
Name: Marco Salazar
Date: 8/26/2020
Assignment: Programming assignment 1

There is no input in this program. The only output will be words printed out using a int array buffer.
there are no post or pre conditions.
*/
#include <stdio.h>
#include <malloc.h>

int dataSegment;

int main() {
	int stackSegment;
	int *heapSegment;
	heapSegment = malloc(100);

	int A[20];
	A[0] = 'M' + 'A'*256 + 'R'*256*256 + 'C'*256*256*256;
	A[1] = 'O'           + '!'*256*256 + '!'*256*256*256;
	A[2] = 0;
	heapSegment[0] = 'M' + 'A'*256 + 'R'*256*256 + 'C'*256*256*256;
	heapSegment[1] = 'O';
	heapSegment[2] = 0;


	char *S = (char *) A;
	printf("Stack Array is:\n %s\n\n", S);
	char *H = (char *) heapSegment;
	printf("Heap Array is:\n %s\n\n", H);

	printf("codeSegment   is located at %20u\n", main);
	printf("dataSegment   is located at %20u\n", &dataSegment);
	printf("heapSegment   is located at %20u\n", heapSegment);
	printf("stackSegment  is located at %20u\n", &stackSegment);
	printf("\n");
	printf("Our StackArray is located at %20u\n", A);
	printf("Our HeapArray  is located at %20u\n", heapSegment);
	printf("Our Pointer    is located at %20u\n", &S);


	return 0;
}