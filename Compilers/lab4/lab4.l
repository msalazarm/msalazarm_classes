%{
/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015

lab4.l
	
Name: Marco Salazar
Date: 02/25/2020
Description: This assignment is meant to link our symbol table work from the previous lab
with our work on the calculator.

This code is meant to work alongside a yacc file like lab4.y

The algorithm is simply scanning
	a) the input is any combination of alphanumeric strings.
	b) the output is the identified tokens
	c) the assumption is that all the input wil be alphanumeric

*/

int mydebug=0;
#include "y.tab.h"
%}


%%

int		{if (mydebug) fprintf(stderr,"INT found\n"); 
		/*This is for the reserved INT word*/return(INT);}

[a-zA-Z][a-zA-Z0-9]*		{/*any valid variable name*/
			if (mydebug) fprintf(stderr,"Letter found\n"); 
			/*return the duplicated string so Yacc can do lookup*/
                       yylval.str=strdup(yytext); return(VARIABLE);}
[0-9][0-9]*	{/*any whole integer*/
		       if (mydebug) fprintf(stderr,"Digit found\n"); 
                       yylval.val=atoi((const char *)yytext); return(INTEGER);}
[ \t]		{/*any whitespace */if (mydebug) fprintf(stderr,"Whitespace found\n");}
[=\-+*/%&|()] 	{/*any special character*/ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}
[;]		{/*any end of statement*/if(mydebug) fprintf(stderr, "return a semicolon %c\n", *yytext);
			return(*yytext);}
\n 		{/*any newline*/ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


