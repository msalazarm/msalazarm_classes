/*
 * Name: Marco Salazar
 * Date: 02/07/2020
 * Description: This assignment is meant to help us understand how a simple symboltable works and to get familiar with this code that we will be
 * working with and modifying for the rest of the class.
 * 
 * Source: This code was taken from https://forgetcode.com/C/101-Symbol-table
 * 
 * Changes:
 *  Comments were added and the code was properly indented
 *  declarations and function prototypes were removed and put into symtable.h
 *  symtable.h was included
 *  
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
 * This function presents the user with options to manually input entries into the symbol table, in future labs we will not be taking user input but we will instead 
 */
void main()
{
    int op,y;
    char la[10];
    do
    {
        printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
        printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t5.MODIFY\n\t6.END\n");
        printf("\n\tEnter your option : ");
        scanf("%d",&op);
        switch(op)
        {
            //all the cases of options to take
            case 1:
                Insert();
                break;
            case 2:
                Display();
                break;
            case 3:
                Delete();
                break;
            case 4:
                printf("\n\tEnter the label to be searched : ");
                scanf("%s",la);
                y=Search(la);
                printf("\n\tSearch Result:");
                if(y==1)
                    printf("\n\tThe label is present in the symbol table\n");
                else
                    printf("\n\tThe label is not present in the symbol table\n");
                break;
            case 5:
                Modify();
                break;
            case 6:
                exit(0);
        }
    }while(op<6);//this loop continues to ask for user input until the user exits.
    
}  /* and of main */

/*
 * This function asks for a label, symbol, and address, and inserts it into the symboltable.
 * if a label already exists it will not insert a duplicate.
 * 
 */
//symbol, where it should be Insert(char *l, int a)
void Insert()
{
    int n;
    char l[10];
    printf("\n\tEnter the label : ");
    scanf("%s",l);
    n=Search(l);
    if(n==1)
        printf("\n\tThe label exists already in the symbol table\n\tDuplicate can.t be inserted");
    else
    {
        struct SymbTab *p;
        p=malloc(sizeof(struct SymbTab));
        strcpy(p->label,l);
        printf("\n\tEnter the symbol : ");
        scanf("%s",p->symbol);
        printf("\n\tEnter the address : ");
        scanf("%d",&p->addr);
        p->next=NULL;
        if(size==0)
        {
            first=p;
            last=p;
        }
        else
        {
            last->next=p;
            last=p;
        }
        size++;
    }
    printf("\n\tLabel inserted\n");
}

/*
 * This function runs through the symbol table and prints out all the entries
 */
void Display()
{
    int i;
    struct SymbTab *p;
    p=first;
    printf("\n\tLABEL\t\tSYMBOL\t\tADDRESS\n");
    for(i=0;i<size;i++)
    {
        printf("\t%s\t\t%s\t\t%d\n",p->label,p->symbol,p->addr);
        p=p->next;
    }
}

/*
 * This function takes in a label and searches the symbol table for that label.
 */
//should take a pointer
int Search(char lab[])
{
    int i,flag=0;
    struct SymbTab *p;
    p=first;
    for(i=0;i<size;i++)
    {
        if(strcmp(p->label,lab)==0)
            flag=1;
        p=p->next;
    }
    return flag;
}

/*
 * This code asks the user what they want to change about a data entry: either the label, the address, or the label and address.
 * After that it asks the user to give the label of the desired entry and then any other relevent information needed to change things.
 */
void Modify()
{
    char l[10],nl[10];
    int add,choice,i,s;
    struct SymbTab *p;
    p=first;
    printf("\n\tWhat do you want to modify?\n");
    printf("\n\t1.Only the label\n\t2.Only the address\n\t3.Both the label and address\n");
    printf("\tEnter your choice : ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("\n\tEnter the old label : ");
            scanf("%s",l);
            s=Search(l);
            if(s==0)
                printf("\n\tLabel not found\n");
            else
            {
                printf("\n\tEnter the new label : ");
                scanf("%s",nl);
                for(i=0;i<size;i++)
                {
                    if(strcmp(p->label,l)==0)
                        strcpy(p->label,nl);
                    p=p->next;
                }
                printf("\n\tAfter Modification:\n");
                Display();
            }
            break;
        case 2:
            printf("\n\tEnter the label where the address is to be modified : ");
            scanf("%s",l);
            s=Search(l);
            if(s==0)
                printf("\n\tLabel not found\n");
            else
            {
                printf("\n\tEnter the new address : ");
                scanf("%d",&add);
                for(i=0;i<size;i++)
                {
                    if(strcmp(p->label,l)==0)
                        p->addr=add;
                    p=p->next;
                }
                printf("\n\tAfter Modification:\n");
                Display();
            }
            break;
        case 3:
            printf("\n\tEnter the old label : ");
            scanf("%s",l);
            s=Search(l);
            if(s==0)
                printf("\n\tLabel not found\n");
            else
            {
                printf("\n\tEnter the new label : ");
                scanf("%s",nl);
                printf("\n\tEnter the new address : ");
                scanf("%d",&add);
                for(i=0;i<size;i++)
                {
                    if(strcmp(p->label,l)==0)
                    {
                        strcpy(p->label,nl);
                        p->addr=add;
                    }
                    p=p->next;
                }
                printf("\n\tAfter Modification:\n");
                Display();
            }
            break;
    }
}

/*
 * This function searches the symbol table for the label entry to be deleted, if it finds it, then it readjusts the linked list so that it is properly linked.
 */
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
}

