In the original instructions, it asks that the getLine() function return the length of the string. If the string exceeds the length it asks
	that it return -1. If the end of file is reached, it asks that EOF be returned. However, I found in the testing of my program that -1 is 
	the same as EOF, therefore it would cause an error and make the program only print out the longest line before a line that exceeds the
	limit.
	
Therefore i changed the behavior of the program so that it returns 101 if the line exceeds the length it should. this prevents the error
	and enables the program to funtion fully.

-Marco Salazar
