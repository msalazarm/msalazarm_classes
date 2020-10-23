         /* 
	1)lab2remove.l

	    simple lex program which removes comments from a source program
            The main key is that a variable "comment" is set when the start of a comment
            is seen and then unset when the ending set is seen.  It is possible to have
            two starts closed by on end.

            Shaun Cooper
            January 2015

	2) Modified by: Marco Salazar
	3) January 31, 2019

	4) The algorithm used was just simple counting of the newlines.
		a) the input is any combination of alphanumeric strings.
		b) the output the inputted file without comments, but with line numbers in error messages.
		c) the assumption is that all the input wil be alphanumeric
	
	Changes to Code: 
		linecount variable was added to count the lines.
		new rule was added to detect newlines, add to linecount, and printf("\n") for the buffer
		errors were updated to include newline.
 
         */
%{
        int comment = 0;
        int debug=1;  /* prints out debug statements if desired */
	int linecount = 1;
%}
%%

"/*"	{
	if (comment && debug) fprintf(stderr,
		" >>>>>>>> line %d: Possible Nested comment <<<<<<<<<<\n", linecount);
	comment = 1;
	}

"*/"	{
          if (!comment) printf("%s",yytext); /*print out if it is not in a comment */
  	  comment = 0;
	}

\n      { 
          linecount = linecount + 1; printf("\n");
	}

.       { if (!comment) printf("%s",yytext);}

%%

int yywrap(void)
{ return 1;
}

int main()
{
  yylex();
  
}

