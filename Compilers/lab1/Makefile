# 
# makefile for lab1
# Marco Salazar
# January 24, 2020
#
# This makefile compiles the code necessary to run ./lab1. if there are any changes made to any of the files, it will recompile.
#

all:	lab1

lab1:	lex.yy.c
	gcc -o lab1 lex.yy.c

lex.yy.c:	wordlengthlab1.l
	lex wordlengthlab1.l
