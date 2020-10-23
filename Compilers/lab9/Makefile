# Makefile for lab9
# Marco Salazar
# may 06, 2020
#
# This makes all the files necessary to run lab9
#

all:
	yacc -d lab9.y
	lex lab9.l
	gcc lex.yy.c y.tab.c ast.c symtable.c emit.c -o lab9

clean:
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
