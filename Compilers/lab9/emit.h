/*
emit.h
	
Name: Marco Salazar
Date: 05/6/2020
Description: This code is a header file for emit.c, it emits all the MIPS code into a file

This is a header file, no inputs outputs or assumptions.

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef EMIT_H
#define EMIT_H

#include "ast.h"
#include "symtable.h"
#define WSIZE 4    //number of bytes in a word
#define LOGWSIZE 2 //number of shifts to get to WSIZE


char * genlabel();
void EMITSTRINGS(ASTNode *p, FILE *fd);
void EMITGLOBALS(ASTNode *p, FILE *fd);
void EMITAST(ASTNode *p, FILE *fp);
#endif // of emit.h
