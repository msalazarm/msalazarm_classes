%{

/* 

This code is meant for lab7. it is meant to be used alongside the lex file
    
lab7.y
    
Name: Marco Salazar
Date: 04/17/2020
Description: This code implements a simple CFG of ALGOL_C and creates the appropriate Abstract Syntax Tree as provided by Shaun Cooper.
and periodically prints out the symbol table.

The algorithms used were just based off of Context Free Grammer. the input was tokens from lex, and the output is answers and errors to the terminal as well as a GlobalTreePointer. 
Under best circumstances we assume that the tokens will be valid and syntax error free, however, if it is not then errors will be printed.
otherwise the symbol table will be printed at the end of each compound_stmt and at the end of parsing.

Changes:
At points where an ID Variable or Function are used, they are added to the symbol table.
None of the names were changed, but this should be used alongside ast.h and ast.c

        
*/


    /* begin specs */
int yylex(); // prototype to get rid of gcc warning
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "symtable.h"
#include "ast.h"

ASTNode *GlobalTreePointer;
extern int mydebug;
extern int linecount;
int isSyntaxError = 0;
int level = 0; // the level of compound statements
int offset = 0; // current offset at the global level or in a function
                // offset is measured in words
int GOFFSET;    // holds the global offset
int MAXOFFSET;  // the maximum amount of memory needed for the current function

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
                                struct SymbTab *s;
                                s = Search(p->Name, level, 0);
                                p->datatype = $1;
                                //updates each of the var_list in the symbol table's Type
                                s->Type = $1;
                                p = p->s1;
                            }
                            }
        ;

var_list	: ID 		{if (mydebug) fprintf(stderr, "at var_list  \n");
                        if (Search($1, level, 0) != NULL) {
                            yyerror("Duplicate Variable ");
                            yyerror($1);
                            exit(1);
                        }else{
                            //inserts the symbol into the symbol table, but without a Type
                            Insert($1, -1, 0, level, 1, offset, NULL);
                            offset= offset + 1; //the size of the object.
                        
                        } // insert the symbol
                        $$ = ASTCreateNode(VARDEC);
                        //connects the ASTNode to its SymbTab
                        $$->symbol = Search($1, level, 0);
                        $$->Name = $1;
                        }
        | ID '[' NUM ']'  	{
                        if (Search($1, level, 0) != NULL) {
                            yyerror("Duplicate Variable ");
                            yyerror($1);
                            exit(1);
                        }else{
                            //inserts the symbol into the symbol table, but without a Type
                            Insert($1, -1, 2, level, $3, offset, NULL);
                            offset= offset + $3; //the size of the object.
                            //Display();
                            //Insert(char *name, enum OPERATORS Type, int isafunc, int  level, int mysize, int offset, ASTNode * fparms );
                        
                        } // insert the symbol
                        $$ = ASTCreateNode(VARDEC);
                        //connects the ASTNode to its SymbTab
                        $$->symbol = Search($1, level, 0);
                        $$->Name = $1;
                        $$->value = $3;
                            }
        | ID ',' var_list 	{if (mydebug) fprintf(stderr, "at var_list  \n");
                        if (Search($1, level, 0) != NULL) {
                            yyerror("Duplicate Variable ");
                            yyerror($1);
                            exit(1);
                        }else{
                            //inserts the symbol into the symbol table, but without a Type
                            Insert($1, -1, 0, level, 1, offset, NULL);
                            offset= offset + 1; //the size of the object.
                            //Display();
                            //Insert(char *name, enum OPERATORS Type, int isafunc, int  level, int mysize, int offset, ASTNode * fparms );
                        
                        } // insert the symbol
                        $$ = ASTCreateNode(VARDEC);
                        //connects the ASTNode to its SymbTab
                        $$->symbol = Search($1, level, 0);
                        $$->Name = $1;
                        $$->s1 = $3;
                            }
        | ID '[' NUM ']' ',' var_list 	{
                        if (Search($1, level, 0) != NULL) {
                            yyerror("Duplicate Variable ");
                            yyerror($1);
                            exit(1);
                        }else{
                            //inserts the symbol into the symbol table, but without a Type
                            Insert($1, -1, 2, level, $3, offset, NULL);
                            offset= offset + $3; //the size of the object.
                            //Display();
                            //Insert(char *name, enum OPERATORS Type, int isafunc, int  level, int mysize, int offset, ASTNode * fparms );
                        
                        } // insert the symbol
                        $$ = ASTCreateNode(VARDEC);
                        //connects the ASTNode to its SymbTab
                        $$->symbol = Search($1, level, 0);
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

func_dec	: type_spec ID '(' {
                                //deal with the offset
                                //check if ID of function is there and if not install it
                                if (Search($2, level, 0) != NULL){
                                    yyerror("Duplicate function  ");
                                    yyerror($2);
                                    exit(1);
                                }else{
                                    //if the function doesn't exist, put it in the table
                                    Insert($2, $1, 1, level, 0, 0, NULL);
                                }
                                //push the offsets so you can pop them back on later
                                GOFFSET = offset; offset = 0; MAXOFFSET = offset;} 
            params ')'          { 
                                    //this updates the formal paramet link in my symbol table
                                    Search($2, level, 0)->fparms = $5;
                                }
            compound_stmt 	    {if (mydebug) fprintf(stderr, "at func_dec  \n"); 
                                $$ = ASTCreateNode(FUNDEC); 
                                $$->Name =$2; 
                                $$->datatype = $1; 
                                $$->s1 = $5;
                                $$->s2 = $8;
                                //connects the ASTNode to its SymbTab
                                $$->symbol = Search($2, level, 0);
                                
                                //pops the offsets back
                                offset =  GOFFSET;
                                //sets this functions max offset to the largest it can be
                                Search($2, 0, 0)->mysize = MAXOFFSET;
                                //Display();
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
                                if (Search($2, level+1, 0) != NULL) {
                                    yyerror("Duplicate Variable ");
                                    yyerror($2);
                                    exit(1);
                                }else{
                                    //inserts the symbol into the symbol table
                                    Insert($2, $1, 0, level+1, 1, offset, NULL);
                                    offset = offset + 1;
                                
                                } // insert the symbol
                                $$ = ASTCreateNode(PARAM);
                                $$->datatype = $1;
                                $$->Name = $2;
                                $$->size = 0;}
        | type_spec ID '[' ']'	{if (mydebug) fprintf(stderr, "at param  \n");
                                if (Search($2, level+1, 0) != NULL) {
                                    yyerror("Duplicate Variable ");
                                    yyerror($2);
                                    exit(1);
                                }else{
                                    //inserts the symbol into the symbol table, but without a Type
                                    Insert($2, $1, 2, level+1, 1, offset, NULL);
                                    offset = offset + 1;
                                
                                } // insert the symbol
                                $$ = ASTCreateNode(PARAM);
                                $$->datatype = $1;
                                $$->Name = $2;
                                $$->size = -1;/*paramater passed as array*/}
        ;
    /*Increases the level since this enters a compound_stmt*/
compound_stmt	: MYBEGIN {level++;} local_declarations statement_list END	{if (mydebug) fprintf(stderr, "at compound_stmt  \n");
                                                                            $$ = ASTCreateNode(BLOCK);
                                                                            $$->s1 = $3;
                                                                            $$->s2 = $4;
                                                                            //shows the current symbol table
                                                                            Display();
                                                                            //changes the maxoffset so that we are garunteed to have the biggest one
                                                                            if (offset > MAXOFFSET) MAXOFFSET = offset;
                                                                            //deletes this level off the symbol table
                                                                            offset -= Delete(level);
                                                                            level--;}
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
                                    if( $1->datatype != $3->datatype)//if the types dont match, barf
                                    {
                                    yyerror("type mismatch on assignment");
                                    exit(1);
                                    }
                                    $$ = ASTCreateNode(ASSIGN);
                                    $$->s1 = $1;
                                    $$->s2 = $3;}
                ;

expression	: simple_expression	{if (mydebug) fprintf(stderr, "at expression  \n");
                                $$ = $1;}
        ;
/* isafunc 0 == scaler,  1 == function, 2 == array*/
var		: ID					{if (mydebug) fprintf(stderr, "at var  \n");
                                    struct SymbTab *s;
                                    //search to see if the symbol exists or not and if it is the correct type
                                    s = Search($1, level, 1);
                                    if (s == NULL){
                                        yyerror("Variable does not exits ");
                                        yyerror($1);
                                        exit(1);
                                    }
                                    if (s->IsAFunc != 0){
                                        yyerror("needs to be a scaler ");
                                        yyerror($1);
                                        exit(1);
                                    }
                                    $$ = ASTCreateNode(MYVAR);
                                    $$->size = 0;//not an array
                                    $$->Name = $1;
                                    $$->symbol = s;// store the pointer to the symbol
                                    $$->datatype = s->Type;
                                    }
        | ID '[' expression ']'	{if (mydebug) fprintf(stderr, "at var  \n");
                                    struct SymbTab *s;
                                    //search to see if the symbol exists or not and if it is the correct type
                                    s = Search($1, level, 1);
                                    if (s == NULL){
                                        yyerror("Array does not exits ");
                                        yyerror($1);
                                        exit(1);
                                    }
                                    if (s->IsAFunc != 2){
                                        yyerror("needs to be an array ");
                                        yyerror($1);
                                        exit(1);
                                    }
                                    $$ = ASTCreateNode(MYVAR);
                                    $$->size = -1;//is an array
                                    $$->Name = $1;
                                    $$->s1 = $3;
                                    $$->symbol = s; // store the pointer to the symbol
                                    $$->datatype = s->Type;
                                    }
        ;

simple_expression	: additive_expression							{if (mydebug) fprintf(stderr, "at simple_expression  \n");
                    $$ = $1;}
            | simple_expression relop additive_expression 		{if (mydebug) fprintf(stderr, "at simple_expression  \n");
                                                                if( $1->datatype != $3->datatype){
                                                                //if the types dont match, barf
                                                                    yyerror("Type mismatch ");
                                                                    exit(1);
                                                                }
                                                                $$ = ASTCreateNode(EXPRESSION);
                                                                $$->op = $2;
                                                                $$->s1 = $1;
                                                                $$->s2 = $3;
                                                                $$->datatype = $1->datatype;
                                                                }
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
                                                if( $1->datatype != $3->datatype){
                                                //if the types dont match, barf
                                                    yyerror("Type mismatch ");
                                                    exit(1);
                                                }
                                                $$ = ASTCreateNode(EXPRESSION);
                                                $$->op = $2;
                                                $$->s1 = $1;
                                                $$->s2 = $3;
                                                $$->datatype = $1->datatype;
                                                }
            ;

addop	: '+'	{if (mydebug) fprintf(stderr, "at addop  \n");
                $$ = MPLUS;}
        | '-'	{if (mydebug) fprintf(stderr, "at addop  \n");
                $$ = MMINUS;}
        ;

term	: factor				{if (mydebug) fprintf(stderr, "at term  \n");
                                $$ = $1;}
        | term multop factor	{if (mydebug) fprintf(stderr, "at term  \n");
                                if( $1->datatype != $3->datatype){
                                //if the types dont match, barf
                                    yyerror("Type mismatch ");
                                    exit(1);
                                }
                                $$ = ASTCreateNode(EXPRESSION);
                                $$->op = $2;
                                $$->s1 = $1;
                                $$->s2 = $3;
                                $$->datatype = $1->datatype;
                                }
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
                                $$->size = $1;
                                $$->datatype = INTTYPE;
                                }
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
                                if($2->datatype != BOOLEANTYPE){
                                //not should only be applied to boolean
                                    yyerror("not needs a BOOLEANTYPE ");
                                    exit(1);
                                }
                                $$ = ASTCreateNode(BOOLNOT);
                                $$->s1 = $2;
                                $$->datatype = $2->datatype;
                                }
        ;

call	: ID '(' args ')'	{if (mydebug) fprintf(stderr, "at call  \n");
                            struct SymbTab *s;
                            //check to see if the function has been defined before
                            s = Search($1, level, 1);
                            if (s == NULL){
                                yyerror("Function has not been defined ");
                                yyerror($1);
                                exit(1);
                            }
                            if (s->IsAFunc != 1){
                                yyerror("needs to be a function ");
                                yyerror($1);
                                exit(1);
                            }
                            //check the formal parameters versus the actual parameters
                            if (check_formals_and_params(s->fparms, $3) != 1){
                                yyerror("function actual and formal parameters mismatch");
                                exit(1);
                            }
                            $$ = ASTCreateNode(CALL);
                            $$->Name = $1;
                            $$->s1 = $3;
                            //link the astnode to the symbol table
                            $$->symbol = s;
                            $$->datatype = s->Type; //comes from symbol table
                            }
        ;

args	: arg_list	{if (mydebug) fprintf(stderr, "at args  \n");
                    $$ = $1;}
        | /*empty*/	{if (mydebug) fprintf(stderr, "at args  \n");
                    $$ = NULL;}
        ;

arg_list	: expression	      	{if (mydebug) fprintf(stderr, "at arg_list  \n");
                                    $$ = ASTCreateNode(ARG);
                                    $$->s1 = $1;
                                    $$->datatype = $1->datatype;
                                    $$->next=NULL;
                                    }
        | expression ',' arg_list	{if (mydebug) fprintf(stderr, "at arg_list  \n");
                                    $$ = ASTCreateNode(ARG);
                                    $$->datatype = $1->datatype;
                                    $$->s1 = $1;
                                    $$->next = $3;}
        ;

%%	/* end of rules, start of program */

int main()
{
yyparse();
//if there has been any syntax error no congratulations message will be given.
if(isSyntaxError){
}
else{
    //print the last instance of the symbol table
    printf("\nMain symbol table START\n");
    Display();
    ASTprint(GlobalTreePointer, 0);
    }
}
