%{
     /*  1) wordlengthlab1.l 
	 
	 This lex routine uses a counting array to match alphabeticstrings 
         and make a frequency count.
  
         The real item to notice is that yywrap() is called at EOF and then is run
         to do what we need to do.   yywrap() returns true when we have a successful 
         end to the program.  We may want to return false (0) if we want to lexing process 
         to fail 

        Shaun Cooper
        January 2015

	2) Modified by: Marco Salazar
	3) January 24, 2019

	4) The algorithm used was just simple counting of the variable.
		a) the input is any combination of alphanumeric strings.
		b) the output is a list of how many of each word length there is and of how many number strings there was
		c) the assumption is that all the input wil be alphanumeric
	

	Changes to Code: 
the global variable count was added. 
the global variable count is incremented whenever a number is found. 
the global variable count is printed in the wrap up code.
a newline character was added to the first printed statement so that the output looks neater.
   */
	int lgths[100];
	int count =0;

%}

%%
[a-zA-Z]+	{lgths[yyleng]++; }
[0-9]+		{count++; }
.	|
\n	;
%%

/*this function is called at the wrap up of the code.
It prints out for each length type of word, how many of them there are.
It also prints out the number of numbers that is found in scanning the words.*/
int yywrap()
{
	int i;
	printf("\nLength  No. words\n");
	for (i=1; i<100; i++) {
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}

	printf("numbers of numbers is %d\n", count);
	return(1);
}

int main()
{  yylex();

}
