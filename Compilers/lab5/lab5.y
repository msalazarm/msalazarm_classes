%{

/* 

This code is meant for lab5. it is meant to be used alongside lab5.l
	
lab5.y
	
Name: Marco Salazar
Date: 03/01/2020
Description: This code implements a simple CFG of ALGOL_C as provided by Shaun Cooper. This code
will be given more syntax directed semantic action in the next lab.

The algorithms used were just based off of Context Free Grammer. the input was tokens from lex, and the output is answers and errors to the terminal. Under best circumstances we assume that the tokens will be valid and syntax error free, however, if it is not then errors will be printed.
		
*/


	/* begin specs */
int yylex(); // prototype to get rid of gcc warning
#include <stdio.h>
#include <ctype.h>

extern int mydebug;
extern int linecount;
int isSyntaxError = 0;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  isSyntaxError = 1;
  printf ("%s on line %d\n", s, linecount);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start program

//tokens for the language
%token INT VOID BOOLEAN MYBEGIN END IF THEN ELSE WHILE DO MYRETURN READ WRITE EQ LE GE NE AND OR TRUE FALSE NOT
%token <val>NUM
%token  <str>ID

//union that allows us to recieve copied strings from lex.
%union {char* str; int val;}

%%	/* end specs, begin rules */

program		: DL 	{if (mydebug) fprintf(stderr, "at program  \n");}
		;
		
//
DL		: DEC	{if (mydebug) fprintf(stderr, "at DL  \n");}
		| DEC DL 	{if (mydebug) fprintf(stderr, "at DL  \n");}
		;

DEC		: var_dec  	 {if (mydebug) fprintf(stderr, "at DEC  \n");}
		| func_dec	 	{if (mydebug) fprintf(stderr, "at DEC  \n");}
		;

var_dec		: type_spec var_list ';' 	{if (mydebug) fprintf(stderr, "at var_dec  \n");}
		;

var_list	: ID 		{if (mydebug) fprintf(stderr, "at var_list  \n");}
		| ID '[' NUM ']'  	{if (mydebug) fprintf(stderr, "at var_list  \n");}
		| ID ',' var_list 	{if (mydebug) fprintf(stderr, "at var_list  \n");}
		| ID '[' NUM ']' ',' var_list 	{if (mydebug) fprintf(stderr, "at var_list  \n");}
		;

type_spec 	: INT 	{if (mydebug) fprintf(stderr, "at type_spec  \n");}
		| BOOLEAN 	{if (mydebug) fprintf(stderr, "at type_spec  \n");}
		| VOID 	    {if (mydebug) fprintf(stderr, "at type_spec  \n");}
		;

func_dec	: type_spec ID '(' params ')' compound_stmt 	{if (mydebug) fprintf(stderr, "at func_dec  \n");}
		;

params		: VOID 	    {if (mydebug) fprintf(stderr, "at params  \n");}
		| param_list 	{if (mydebug) fprintf(stderr, "at params  \n");}
		;

param_list	: param     	        {if (mydebug) fprintf(stderr, "at param_list  \n");}
		|  param ',' param_list  	{if (mydebug) fprintf(stderr, "at param_list  \n");}
		;

param 		: type_spec ID		{if (mydebug) fprintf(stderr, "at param  \n");}
		| type_spec ID '[' ']'	{if (mydebug) fprintf(stderr, "at param  \n");}
		;

compound_stmt	: MYBEGIN local_declarations statement_list END	{if (mydebug) fprintf(stderr, "at compound_stmt  \n");}
		;

local_declarations	: var_dec local_declarations	{if (mydebug) fprintf(stderr, "at local_declarations  \n");}
			| /*empty*/
			;

statement_list	: statement	statement_list  {if (mydebug) fprintf(stderr, "at statement_list  \n");}
		| /*empty*/
		;

statement	: expression_stmt	{if (mydebug) fprintf(stderr, "at statement  \n");}
		| compound_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");}
		| selection_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");}
		| iteration_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");}
		| assignment_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");}
		| return_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");}
		| read_stmt				{if (mydebug) fprintf(stderr, "at statement  \n");}
		| write_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");}
		;

expression_stmt	: expression ';'	{if (mydebug) fprintf(stderr, "at expression_stmt  \n");}
		| ';'           			{if (mydebug) fprintf(stderr, "at expression_stmt  \n");}
		;

selection_stmt	: IF expression THEN statement			{if (mydebug) fprintf(stderr, "at selection_stmt  \n");}
		| IF expression THEN statement ELSE statement	{if (mydebug) fprintf(stderr, "at selection_stmt  \n");}
		;

iteration_stmt	: WHILE expression DO statement			{if (mydebug) fprintf(stderr, "at iteration_stmt  \n");}
		;

return_stmt	: MYRETURN ';'			{if (mydebug) fprintf(stderr, "at return_stmt  \n");}
		| MYRETURN expression ';'	{if (mydebug) fprintf(stderr, "at return_stmt  \n");}
		;

read_stmt	: READ var ';'	{if (mydebug) fprintf(stderr, "at read_stmt  \n");}
		;

write_stmt	: WRITE expression ';'	{if (mydebug) fprintf(stderr, "at write_stmt  \n");}
		;


assignment_stmt	: var '=' simple_expression ';'	{if (mydebug) fprintf(stderr, "at assignment_stmt  \n");}
				;

expression	: simple_expression	{if (mydebug) fprintf(stderr, "at expression  \n");}
		;

var		: ID					{if (mydebug) fprintf(stderr, "at var  \n");}
		| ID '[' expression ']'	{if (mydebug) fprintf(stderr, "at var  \n");}
		;

simple_expression	: additive_expression							{if (mydebug) fprintf(stderr, "at simple_expression  \n");}
			| simple_expression relop additive_expression 		{if (mydebug) fprintf(stderr, "at simple_expression  \n");}
			;

relop	: LE	{if (mydebug) fprintf(stderr, "at relop  \n");}
		| '>'	{if (mydebug) fprintf(stderr, "at relop  \n");}
		| '<'	{if (mydebug) fprintf(stderr, "at relop  \n");}
		| GE	{if (mydebug) fprintf(stderr, "at relop  \n");}
		| EQ	{if (mydebug) fprintf(stderr, "at relop  \n");}
		| NE	{if (mydebug) fprintf(stderr, "at relop  \n");}
		;

additive_expression	: term		{if (mydebug) fprintf(stderr, "at additive_expression  \n");}
			| additive_expression addop term	{if (mydebug) fprintf(stderr, "at additive_expression  \n");}
			;

addop	: '+'	{if (mydebug) fprintf(stderr, "at addop  \n");}
		| '-'	{if (mydebug) fprintf(stderr, "at addop  \n");}
		;

term	: factor				{if (mydebug) fprintf(stderr, "at term  \n");}
		| term multop factor	{if (mydebug) fprintf(stderr, "at term  \n");}
		;

multop	: '*'	{if (mydebug) fprintf(stderr, "at multop  \n");}
		| '/'	{if (mydebug) fprintf(stderr, "at multop  \n");}
		| AND	{if (mydebug) fprintf(stderr, "at multop  \n");}
		| OR	{if (mydebug) fprintf(stderr, "at multop  \n");}
		;

factor	: '(' expression ')'	{if (mydebug) fprintf(stderr, "at factor  \n");}
		| NUM					{if (mydebug) fprintf(stderr, "at factor  \n");}
		| var					{if (mydebug) fprintf(stderr, "at factor  \n");}
		| call					{if (mydebug) fprintf(stderr, "at factor  \n");}
		| TRUE					{if (mydebug) fprintf(stderr, "at factor  \n");}
		| FALSE					{if (mydebug) fprintf(stderr, "at factor  \n");}
		| NOT factor			{if (mydebug) fprintf(stderr, "at factor  \n");}
		;

call	: ID '(' args ')'	{if (mydebug) fprintf(stderr, "at call  \n");}
		;

args	: arg_list	{if (mydebug) fprintf(stderr, "at args  \n");}
		| /*empty*/	{if (mydebug) fprintf(stderr, "at args  \n");}
		;

arg_list	: expression	      	{if (mydebug) fprintf(stderr, "at arg_list  \n");}
		| expression ',' arg_list	{if (mydebug) fprintf(stderr, "at arg_list  \n");}
		;

%%	/* end of rules, start of program */

int main()
{
  yyparse();
  //if there has been any syntax error no congratulations message will be given.
  if(isSyntaxError){
  }
  else{
    fprintf(stderr, "the input is syntactically correct\n");
    }
}
