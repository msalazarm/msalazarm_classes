/*
symtable.h

Name: Marco Salazar
Date: 02/25/2020
Description: This assignment is meant to link our symbol table work from the previous lab
with our work on the calculator.

This is the header file for symtable.c

 */
#include<stdio.h>
/* #include<conio.h> */
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#ifndef SYMTAB
#define SYMBTAB
void Insert(char* insymb, int offset);
void Display();
int FetchAddress(char* symb);
//void Delete();
int Search(char* sym);
//void Modify();

//Data structure to make a linked list symbol table
struct SymbTab
{
    char* symbol;
    int addr;
    struct SymbTab *next;
    
};

#endif
