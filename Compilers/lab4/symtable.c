/*
symtable.c

Name: Marco Salazar
Date: 02/25/2020
Description: This assignment is meant to link our symbol table work from the previous lab
with our work on the calculator.

This file has no new algorithm other than iterating through a linked list. it simply takes in some strings or ints and then inserts them into the symbol table, searches for the symbol, or gets a symbols address.

 */
#include<stdio.h>
/* #include<conio.h> */
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include "symtable.h"
int size=0;

//pointers to the first node and the last node
struct SymbTab *first,*last;

/*
 * uncomment main if you need to test the symbol table by itself.
 */
/*
void main()
{
	printf("search returns %d\n", Search("myfirst"));
	Insert("myfirst", 0);
	Insert("mysecond", 1);
	Insert("mythird", 2);
	printf("serach returns %d\n", Search("myfirst"));
	Display();
    
}  */ /* and of main */

/*
 * This function asks for a symbol, and address, and inserts it into the symboltable.
 * if a symbol already exists it will not insert a duplicate.
 * 
Pre condition: insymb is a valid string.
post condition: the symbol with its offset will be inserted.
 */
void Insert(char* insymb, int offset)
{
    int n;
    n=Search(insymb);
    if(n==1)
        printf("\n\tThe label exists already in the symbol table\n\tDuplicate can.t be inserted");
    else//symbol not inserted yet
    {
        struct SymbTab *p;
        p=malloc(sizeof(struct SymbTab));
	p->symbol = strdup(insymb);
	p->addr = offset;
        p->next=NULL;
        if(size==0)//set pointer as only node
        {
            first=p;
            last=p;
        }
        else//add pointer to the end
        {
            last->next=p;
            last=p;
        }
        size++;
    }
}

/*
 * This function runs through the symbol table and prints out all the entries
precondition: none.
postcondition: the table will be printed
 */
void Display()
{
    int i;
    struct SymbTab *p;
    p=first;
    printf("\n\tSYMBOL\t\tADDRESS\n");
    for(i=0;i<size;i++)//iterate through table
    {
        printf("\t%s\t\t%d\n",p->symbol,p->addr);
        p=p->next;
    }
}

/*
 * This function takes in a symbol and searches the symbol table for that symbol.
precondition: sym must be a valid string
postcondition: 1 for found, 0 for not found
 */
int Search(char* sym)
{
    int i,flag=0;
    struct SymbTab *p;
    p=first;
    for(i=0;i<size;i++)//iterate throughtable
    {
        if(strcmp(p->symbol,sym)==0)//check if current symbol and sym are equal
            flag=1;
        p=p->next;
    }
    return flag;
}

/*
 * This function takes in a symbol name, and returns its address 
precondition: symb is a valid string, and is in the symbol table.
postcondition: returns the address if found, or -1 if not found.
 */
int FetchAddress(char* symb){
	int i = 0;
	int returnaddress = -1;
	struct SymbTab *p;
	p=first;
	for(i = 0; i< size; i++){//iterate through symbol table
		if(strcmp(p->symbol,symb)==0) returnaddress = p->addr;
	p=p->next;
	}
	return returnaddress;
}


/*
  To be fixed later in lab 6

 * This function searches the symbol table for the label entry to be deleted, if it finds it, then it readjusts the linked list so that it is properly linked.
 */
/*
void Delete()
{
    int a;
    char l[10];
    struct SymbTab *p,*q;
    p=first;
    printf("\n\tEnter the label to be deleted : ");
    scanf("%s",l);
    a=Search(l);
    if(a==0)//label is not found
        printf("\n\tLabel not found\n");
    else
    {
        if(strcmp(first->label,l)==0)// if the label is in the first entry
            first=first->next;
        else if(strcmp(last->label,l)==0)// if the label is in the last entry
        {
            q=p->next;
            while(strcmp(q->label,l)!=0)
            {
                p=p->next;
                q=q->next;
            }
            p->next=NULL;
            last=p;
        }
        else// if the label is a middle entry
        {
            q=p->next;
            while(strcmp(q->label,l)!=0)
            {
                p=p->next;
                q=q->next;
            }
            p->next=q->next;
        }
        size--;
        printf("\n\tAfter Deletion:\n");
        Display();
    }
}*/

