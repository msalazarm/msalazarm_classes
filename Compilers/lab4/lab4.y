%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   We define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

   Shaun Cooper
    January 2015

	
lab4.y
	
Name: Marco Salazar
Date: 02/25/2020
Description: This assignment is meant to link our symbol table work from the previous lab
with our work on the calculator.

The algorithms used were just based off of Context Free Grammer. the input was tokens from lex, and the output is answers and errors to the terminal. Under best circumstances we assume that the tokens will be valid and syntax error free, however, if it is not then errors will be printed.
		
*/


	/* begin specs */
int yylex(); // prototype to get rid of gcc warning
#include <stdio.h>
#include <ctype.h>
#include "symtable.h"
//the predefined variable sets the amount of variables allowed in the calculator.
#define MAXVARS 2
int regs[MAXVARS];
//offset tells how many of the variables have been used.
int offset = 0;
int base, debugsw;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start program

//tokens for the language
%token INT
%token <val>INTEGER
%token  <str>VARIABLE
%type <val>expr

//union that allows us to recieve copied strings from lex.
%union {char* str; int val;}

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

//every program begins with declarations and then a list of commands.
program :	DECLS list
	;

//every DECLS can either be empty or a DEC followed by more DECLS, this ensures that all declarations are first.
DECLS	:	DEC DECLS
	| /*empty*/
	;

// This code defines a variable in our regs array, but searches to see first if it is already full or if the variable has been defined before.
DEC	:	INT VARIABLE ';' '\n' {if(Search($2)==0 && !(offset >= MAXVARS))Insert($2, offset++);
				       else if(Search($2) == 1) fprintf(stderr,"error: the variable %s is already defined\n", $2); else fprintf(stderr, "error: number of variables stored is already at the maximum number of %d\n", MAXVARS);}
	;


//the beginning of mathematical commands.
list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;
// either an expression or variable being assigned a number. 
stat	:	expr
			{ fprintf(stderr,"the answer is %d\n", $1); }
	|	VARIABLE '=' expr
			{ if(Search($1) == 0) fprintf(stderr, "error: the variable %s does not exist\n", $1); else regs[FetchAddress($1)] = $3; }
	;

//all valid math rules in this calculator.
//special rules if it is a variable to check if it has been defined before.
expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '*' expr
			{ $$ = $1 * $3; }
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	VARIABLE
			{ if(Search($1) == 0) fprintf(stderr,"error: could not find variable %s\n", $1);
			  $$ = regs[FetchAddress($1)];}
	|	INTEGER {$$=$1; fprintf(stderr,"found an integer\n");}
	;



%%	/* end of rules, start of program */

int main()
{ yyparse();
}
