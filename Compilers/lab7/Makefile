# Makefile for lab7
# Marco Salazar
# March 29, 2020
#
# This makes all the files necessary to run lab7
#

all:
	yacc -d lab7.y
	lex lab7.l
	gcc lex.yy.c y.tab.c ast.c symtable.c -o lab7

clean:
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
