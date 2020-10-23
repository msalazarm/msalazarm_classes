/*
 * Name: Marco Salazar
 * Date: 02/07/2020
 * Description: This assignment is meant to help us understand how a simple symboltable works and to get familiar with this code that we will be
 * working with and modifying for the rest of the class.
 * 
 * This is the header file for symtable.c
 * 
 */
#include<stdio.h>
/* #include<conio.h> */
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#ifndef SYMTAB
#define SYMBTAB
void Insert();
void Display();
void Delete();
int Search(char lab[]);void Modify();

//Data structure to make a linked list symbol table
struct SymbTab
{
    char label[10],symbol[10];
    int addr;
    struct SymbTab *next;
    
};

#endif
