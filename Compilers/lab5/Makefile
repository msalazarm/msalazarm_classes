# Makefile for lab5
# Marco Salazar
# March 01, 2020
#
# This makes all the files necessary to run lab5
#

all:
	yacc -d lab5.y
	lex lab5.l
	gcc lex.yy.c y.tab.c -o lab5
