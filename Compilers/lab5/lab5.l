%{
/*          
       
Small LEX routine which returns two formal tokens (ID and VAR)
along with single string elements like '+'.

lab5.l
	
Name: Marco Salazar
Date: 03/01/2020
Description: This code is meant to work alongside a yacc file like lab5.y. 
This program implements an ALGOL_C based language as specified by Shaun Cooper.

The algorithm is simply scanning
	a) the input is any combination of alphanumeric strings.
	b) the output is the identified tokens
	c) the assumption is that all the input wil be alphanumeric

*/

int mydebug=0;
int linecount = 1;
#include "y.tab.h"
%}

%%

int 		{if (mydebug) fprintf(stderr,"token found INT \n");
                 return(INT); }
void		{if (mydebug) fprintf(stderr,"token found VOID\n");
                 return(VOID);}
boolean		{if (mydebug) fprintf(stderr,"token found BOOLEAN\n");
                 return(BOOLEAN);}
"begin"		{if (mydebug) fprintf(stderr,"token found MYBEGIN\n");
                 return(MYBEGIN);}
"end"		{if (mydebug) fprintf(stderr,"token found END\n");
                 return(END);}
if		{if (mydebug) fprintf(stderr,"token found IF\n");
                 return(IF);}
then		{if (mydebug) fprintf(stderr,"token found THEN\n");
                 return(THEN);}
else		{if (mydebug) fprintf(stderr,"token found ELSE\n");
                 return(ELSE);}
while		{if (mydebug) fprintf(stderr,"token found WHILE\n");
                 return(WHILE);}
do		{if (mydebug) fprintf(stderr,"token found DO\n");
                 return(DO);}
return		{if (mydebug) fprintf(stderr,"token found MYRETURN\n");
                 return(MYRETURN);}
read		{if (mydebug) fprintf(stderr,"token found READ\n");
                 return(READ);}
write		{if (mydebug) fprintf(stderr,"token found WRITE\n");
                 return(WRITE);}
"=="		{if (mydebug) fprintf(stderr,"token found EQ\n");
                 return(EQ);}
"<="		{if (mydebug) fprintf(stderr,"token found LE\n");
                 return(LE);}
">="		{if (mydebug) fprintf(stderr,"token found GE\n");
                 return(GE);}
"!="		{if (mydebug) fprintf(stderr,"token found NE\n");
                 return(NE);}

and		{if (mydebug) fprintf(stderr,"token found AND\n");
                 return(AND);}
or		{if (mydebug) fprintf(stderr,"token found OR\n");
                 return(OR);}
true		{if (mydebug) fprintf(stderr,"token found TRUE\n");
                 return(TRUE);}
false		{if (mydebug) fprintf(stderr,"token found FALSE\n");
                 return(FALSE);}
not		{if (mydebug) fprintf(stderr,"token found NOT\n");
                 return(NOT);}


[a-zA-Z][a-zA-Z0-9]*	{/*any valid variable name*/
			if (mydebug) fprintf(stderr,"ID found %s\n", yytext); 
			/*return the duplicated string so Yacc can do lookup*/
                       yylval.str=strdup(yytext); return(ID);}

[0-9][0-9]*		{/*any whole integer*/
		       if (mydebug) fprintf(stderr,"Digit found %s\n", yytext); 
                       yylval.val=atoi((const char *)yytext); return(NUM);}

[ \t]			{/*any whitespace */ if (mydebug) fprintf(stderr,"Whitespace found\n");}

[*/()+=\-<>,\[\];]	{/*any special character*/ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}

\n			{/*any newline*/ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                        linecount++;}
%%

int yywrap(void)
{ return 1;}


