# 
# makefile for lab2.2
# Marco Salazar
# January 31, 2020
#
# This makefile compiles the code necessary to run ./lab2.2 if there are any changes made to any of the files, it will recompile.
#
# 1) YACC creates the files y.tab.c and y.tab.h
# 2) Lex creates lex.yy.c
# 3) We do not compile the lex output directly because we include it already inside the yacc code, so the yacc compilation takes care of it so that the yacc file can get the tokens
#

all:	lab2docalc

lab2docalc:	y.tab.c
	gcc -o lab2docalc y.tab.c

y.tab.c:	lex.yy.c lab2docalc.y
	yacc -d lab2docalc.y

lex.yy.c:  lab2docalc.l
	lex lab2docalc.l
