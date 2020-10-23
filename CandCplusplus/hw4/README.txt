I strayed only slightly from the original design of the lab in that i did not use the given function
	eval_expr_4() because it was not necessary to create a fully functional calculator tokenizer.

I discovered that instead of waiting until the end to process the characters that I already had
	I could just combine characters (while paying attention to the order of operations)
	in the function eval_expr_3() while still keeping the recursive nature of the program.

Therefore my eval_expr_4() fill in the blanks are filled with code that just redirects them to the
	eval_expr_3 function. It is never called so it is not a problem.

I have included the tokenizer.o tokenizer.c files from canvas that the professor gave, as well as the
	tokenizer.h file that was made for the last lab, and the copy of data for your convenience.

Have a great day!
-Marco Salazar
