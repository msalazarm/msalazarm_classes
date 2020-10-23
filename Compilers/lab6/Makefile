# Makefile for lab6
# Marco Salazar
# March 29, 2020
#
# This makes all the files necessary to run lab6
#

all:
	yacc -d lab6.y
	lex lab6.l
	gcc lex.yy.c y.tab.c ast.c -o lab6
