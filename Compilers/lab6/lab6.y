%{

/* 

This code is meant for lab6. it is meant to be used alongside the lex file
	
lab6.y
	
Name: Marco Salazar
Date: 03/29/2020
Description: This code implements a simple CFG of ALGOL_C and creates the appropriate Abstract Syntax Tree as provided by Shaun Cooper.

The algorithms used were just based off of Context Free Grammer. the input was tokens from lex, and the output is answers and errors to the terminal as well as a GlobalTreePointer. 
Under best circumstances we assume that the tokens will be valid and syntax error free, however, if it is not then errors will be printed.

Changes:
Each of the production rules now also has Semantic action that creates an Abstract Syntax Tree to be used in later labs. 
None of the names were changed, but this should be used alongside ast.h and ast.c

		
*/


	/* begin specs */
int yylex(); // prototype to get rid of gcc warning
#include <stdio.h>
#include <ctype.h>
#include "ast.h"

ASTNode *GlobalTreePointer;
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

//All the rules that use nodes
%type <node> var_list var_dec DEC DL func_dec params param_list param compound_stmt local_declarations statement_list statement write_stmt expression simple_expression additive_expression term factor var read_stmt return_stmt assignment_stmt expression_stmt iteration_stmt selection_stmt call args arg_list
//all the rules that use a datatype
%type <datatypes> type_spec
//all the rules that return operators
%type <operators> addop relop multop

//union that allows us to recieve copied strings from lex.
%union {char* str; int val; struct ASTNodeType* node; enum DATATYPE datatypes; enum OPERATORS operators;}

%%	/* end specs, begin rules */

program		: DL 	{if (mydebug) fprintf(stderr, "at program  \n");
                            GlobalTreePointer = $1;
                            }
		;
		

DL		: DEC	{if (mydebug) fprintf(stderr, "at DL  \n");
                            $$=$1;
                            }
		| DEC DL 	{if (mydebug) fprintf(stderr, "at DL  \n");
                            $$=$1;
                            $1->next = $2;
                            }
		;

DEC		: var_dec  	 {if (mydebug) fprintf(stderr, "at DEC  \n");
                            $$=$1;
                            }
		| func_dec	 	{if (mydebug) fprintf(stderr, "at DEC  \n");
                            $$=$1;
                            }
		;

var_dec		: type_spec var_list ';' 	{if (mydebug) fprintf(stderr, "at var_dec  \n");
                            $$=$2;
                            ASTNode *p;
                            p = $2;
                            //this code adds the datatype ot all of the var list
                            while(p != 0){
                              p->datatype = $1;
                              p = p->s1;
                            }
                            }
		;

var_list	: ID 		{if (mydebug) fprintf(stderr, "at var_list  \n");
                         $$ = ASTCreateNode(VARDEC);
                         $$->Name = $1;
                        }
		| ID '[' NUM ']'  	{
                         $$ = ASTCreateNode(VARDEC);
                         $$->Name = $1;
                         $$->value = $3;
                            }
		| ID ',' var_list 	{if (mydebug) fprintf(stderr, "at var_list  \n");
                         $$ = ASTCreateNode(VARDEC);
                         $$->Name = $1;
                         $$->s1 = $3;
                            }
		| ID '[' NUM ']' ',' var_list 	{
                         $$ = ASTCreateNode(VARDEC);
                         $$->Name = $1;
                         $$->value = $3;
                         $$->s1 = $6;
                            }
		;

type_spec 	: INT 	{if (mydebug) fprintf(stderr, "at type_spec  \n");
                    $$ = INTTYPE;}
		| BOOLEAN 	{if (mydebug) fprintf(stderr, "at type_spec  \n");
                    $$ = BOOLEANTYPE;}
		| VOID 	    {if (mydebug) fprintf(stderr, "at type_spec  \n");
                    $$ = VOIDTYPE;}
		;

func_dec	: type_spec ID '(' params ')' compound_stmt 	{if (mydebug) fprintf(stderr, "at func_dec  \n"); 
                    $$ = ASTCreateNode(FUNDEC); 
                    $$->Name =$2; 
                    $$->datatype = $1; 
                    $$->s1 = $4;
                    $$->s2 = $6;
                    }
		;

params		: VOID 	    {if (mydebug) fprintf(stderr, "at params  \n"); 
                        $$ = NULL;}
		| param_list 	{if (mydebug) fprintf(stderr, "at params  \n"); 
                        $$ = $1;}
		;

param_list	: param     	        {if (mydebug) fprintf(stderr, "at param_list  \n");
                                    $$ = $1;}
		|  param ',' param_list  	{if (mydebug) fprintf(stderr, "at param_list  \n");
                                    $1->next = $3; $$= $1;}
		;

param 		: type_spec ID		{if (mydebug) fprintf(stderr, "at param  \n");
                                $$ = ASTCreateNode(PARAM);
                                $$->datatype = $1;
                                $$->Name = $2;
                                $$->size = 0;}
		| type_spec ID '[' ']'	{if (mydebug) fprintf(stderr, "at param  \n");
                                $$ = ASTCreateNode(PARAM);
                                $$->datatype = $1;
                                $$->Name = $2;
                                $$->size = -1;/*paramater passed as array*/}
		;

compound_stmt	: MYBEGIN local_declarations statement_list END	{if (mydebug) fprintf(stderr, "at compound_stmt  \n");
                $$ = ASTCreateNode(BLOCK);
                $$->s1 = $2;
                $$->s2 = $3;}
		;

local_declarations	: var_dec local_declarations	{if (mydebug) fprintf(stderr, "at local_declarations  \n");
                                                    $$ = $1;
                                                    $$->next = $2;}
			| /*empty*/                              {$$ = NULL;}
			;

statement_list	: statement	statement_list  {if (mydebug) fprintf(stderr, "at statement_list  \n");
                                            $$ = $1;
                                            $$->next = $2;
                                            }
		| /*empty*/                         {$$= NULL;}
		;

statement	: expression_stmt	{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| compound_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| selection_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| iteration_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| assignment_stmt		{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| return_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| read_stmt				{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		| write_stmt			{if (mydebug) fprintf(stderr, "at statement  \n");
                                $$ = $1;}
		;

expression_stmt	: expression ';'	{if (mydebug) fprintf(stderr, "at expression_stmt  \n");
                                    $$ = ASTCreateNode(EXPRESSIONSTMT);
                                    $$->s1 = $1;}
		| ';'           			{if (mydebug) fprintf(stderr, "at expression_stmt  \n");
                                    $$ = ASTCreateNode(EMPTY);
                                    //EMPTY is used to signifiy nothing, and get rid of errors
                                    }
		;

selection_stmt	: IF expression THEN statement			{if (mydebug) fprintf(stderr, "at selection_stmt  \n");
                                                        $$ = ASTCreateNode(MYIFTHEN);
                                                        $$->s1 = $2;
                                                        //IFELSE serves as a body
                                                        $$->s2 = ASTCreateNode(IFELSE);
                                                        $$->s2->s1 = $4;
                                                        $$->s2->s2 = ASTCreateNode(EMPTY);}
		| IF expression THEN statement ELSE statement	{if (mydebug) fprintf(stderr, "at selection_stmt  \n");
                                                        $$ = ASTCreateNode(MYIFTHEN);
                                                        $$->s1 = $2;
                                                        //IFELSE serves as a body
                                                        $$->s2 = ASTCreateNode(IFELSE);
                                                        $$->s2->s1 = $4;
                                                        $$->s2->s2 = $6;}
		;

iteration_stmt	: WHILE expression DO statement			{if (mydebug) fprintf(stderr, "at iteration_stmt  \n");
                                    $$ = ASTCreateNode(MYWHILE);
                                    $$->s1 = $2;
                                    $$->s2 = $4;}
		;

return_stmt	: MYRETURN ';'			{if (mydebug) fprintf(stderr, "at return_stmt  \n");
                                    $$ = ASTCreateNode(MRETURN);
                                    $$->size = -1;/*This means it was a void return*/}
		| MYRETURN expression ';'	{if (mydebug) fprintf(stderr, "at return_stmt  \n");
                                    $$ = ASTCreateNode(MRETURN);
                                    $$->s1 = $2;}
		;

read_stmt	: READ var ';'	{if (mydebug) fprintf(stderr, "at read_stmt  \n");
                                    $$ = ASTCreateNode(MYREAD);
                                    $$->s1 = $2;}
		;

write_stmt	: WRITE expression ';'	{if (mydebug) fprintf(stderr, "at write_stmt  \n");
                                    $$ = ASTCreateNode(MYWRITE);
                                    $$->s1 = $2;}
		;


assignment_stmt	: var '=' simple_expression ';'	{if (mydebug) fprintf(stderr, "at assignment_stmt  \n");
                                    $$ = ASTCreateNode(ASSIGN);
                                    $$->s1 = $1;
                                    $$->s2 = $3;}
				;

expression	: simple_expression	{if (mydebug) fprintf(stderr, "at expression  \n");
                                $$ = $1;}
		;

var		: ID					{if (mydebug) fprintf(stderr, "at var  \n");
                                    $$ = ASTCreateNode(MYVAR);
                                    $$->size = 0;//not an array
                                    $$->Name = $1;}
		| ID '[' expression ']'	{if (mydebug) fprintf(stderr, "at var  \n");
                                    $$ = ASTCreateNode(MYVAR);
                                    $$->size = -1;//is an array
                                    $$->Name = $1;
                                    $$->s1 = $3;}
		;

simple_expression	: additive_expression							{if (mydebug) fprintf(stderr, "at simple_expression  \n");
                    $$ = $1;}
			| simple_expression relop additive_expression 		{if (mydebug) fprintf(stderr, "at simple_expression  \n");
                                                                $$ = ASTCreateNode(EXPRESSION);
                                                                $$->op = $2;
                                                                $$->s1 = $1;
                                                                $$->s2 = $3;}
			;

relop	: LE	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MLE;}
		| '>'	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MGT;}
		| '<'	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MLT;}
		| GE	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MGE;}
		| EQ	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MEQ;}
		| NE	{if (mydebug) fprintf(stderr, "at relop  \n");
                $$ = MNE;}
		;

additive_expression	: term		{if (mydebug) fprintf(stderr, "at additive_expression  \n");
                                $$ = $1;}
			| additive_expression addop term	{if (mydebug) fprintf(stderr, "at additive_expression  \n");
                                $$ = ASTCreateNode(EXPRESSION);
                                $$->op = $2;
                                $$->s1 = $1;
                                $$->s2 = $3;}
			;

addop	: '+'	{if (mydebug) fprintf(stderr, "at addop  \n");
                $$ = MPLUS;}
		| '-'	{if (mydebug) fprintf(stderr, "at addop  \n");
                $$ = MMINUS;}
		;

term	: factor				{if (mydebug) fprintf(stderr, "at term  \n");
                                $$ = $1;}
		| term multop factor	{if (mydebug) fprintf(stderr, "at term  \n");
                                $$ = ASTCreateNode(EXPRESSION);
                                $$->op = $2;
                                $$->s1 = $1;
                                $$->s2 = $3;}
		;

multop	: '*'	{if (mydebug) fprintf(stderr, "at multop  \n");
                $$ = MMULT;}
		| '/'	{if (mydebug) fprintf(stderr, "at multop  \n");
                $$ = MDIVIDE;}
		| AND	{if (mydebug) fprintf(stderr, "at multop  \n");
                $$ = MAND;}
		| OR	{if (mydebug) fprintf(stderr, "at multop  \n");
                $$ = MOR;}
		;

factor	: '(' expression ')'	{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = $2;}
		| NUM				    {
                                $$ = ASTCreateNode(MYNUM);
                                $$->size = $1;}
		| var					{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = $1;}
		| call					{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = $1;}
		| TRUE					{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = ASTCreateNode(MYNUM);//changed from MBOOL to MYNUM to match the example output
                                $$->size = 1;
                                $$->datatype = BOOLEANTYPE;}
		| FALSE					{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = ASTCreateNode(MYNUM);//changed from MBOOL to MYNUM to match the example output
                                $$->size = 0;
                                $$->datatype = BOOLEANTYPE;}
		| NOT factor			{if (mydebug) fprintf(stderr, "at factor  \n");
                                $$ = ASTCreateNode(BOOLNOT);
                                $$->s1 = $2;}
		;

call	: ID '(' args ')'	{if (mydebug) fprintf(stderr, "at call  \n");
                            $$ = ASTCreateNode(CALL);
                            $$->Name = $1;
                            $$->s1 = $3;}
		;

args	: arg_list	{if (mydebug) fprintf(stderr, "at args  \n");
                    $$ = $1;}
		| /*empty*/	{if (mydebug) fprintf(stderr, "at args  \n");
                    $$ = NULL;}
		;

arg_list	: expression	      	{if (mydebug) fprintf(stderr, "at arg_list  \n");
                                    $$ = ASTCreateNode(ARG);
                                    $$->s1 = $1;}
		| expression ',' arg_list	{if (mydebug) fprintf(stderr, "at arg_list  \n");
                                    $$ = ASTCreateNode(ARG);
                                    $$->s1 = $1;
                                    $$->s2 = $3;}
		;

%%	/* end of rules, start of program */

int main()
{
  yyparse();
  //if there has been any syntax error no congratulations message will be given.
  if(isSyntaxError){
  }
  else{
    ASTprint(GlobalTreePointer, 0);
    }
}
