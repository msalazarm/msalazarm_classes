# 
# makefile for lab2.1
# Marco Salazar
# January 31, 2020
#
# This makefile compiles the code necessary to run ./lab2.1 if there are any changes made to any of the files, it will recompile.
#

all:	lab2.1

lab2.1:	lex.yy.c
	gcc -o lab2.1 lex.yy.c

lex.yy.c:	lab2remove.l
	lex lab2remove.l
