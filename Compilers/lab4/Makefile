# Makefile for lab4
# Marco Salazar
# Feb 25, 2020
#
# This makes all the files necessary to run lab4
#

all:
	yacc -d lab4.y
	lex lab4.l
	gcc lex.yy.c y.tab.c symtable.c -o lab4
