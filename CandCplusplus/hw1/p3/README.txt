	The following C file eq.c is a smart file that puts spaces around equalities (=, ==, !=), only if it is reasonable to believe that the input data is suggesting some equality.
for example: w=w w!=w w==w    
    becomes: w = w w != w w == w
    example: w ==w w =w w !=w or w== w w= w w!= w    
    becomes: w == w w = w w != w or w == w w = w w != w

	However, since there is no reasonable explanation for an equality occuring directly after a tab(\t), a newline(\n) or more than one space (  ) the following output should be expected.
( "\" will be used to indicate either \t or \n or two or more spaces)
for example: w\=w w\==w w\!=w      
   stays as: w\=w w\==w w\!=w
    example: w=\w w==\w w!=\w
   stays as: w=\w w==\w w!=\w

	If there is logical reason to believe that the input is suggesting some form of equality, the appropriate spaces will be inserted as needed.


	The program operates under branching possibilities, using the above mentioned word. With an array that has six spots. Whenever there is a newline, tab, or double space, the array is reset to 0. whenever a character is printed that is not a tab, newline, =, ! or space; the array is first reset then array[0] becomes the value of ch. if the next character is space, array[1] becomes 32(space character), if it is just either ! or = it enters the complex logic. there is one major branch for if array[1] is 32 (the results are printed up to the point where it must be determined whether there is a space on the right), and one major branch for array[1] being zero(no space was printed therfore the result is printed at the end).
	the program then will follow these branches and print the results, in the cases of there being no spaces and no possibility of equality no spaces are added. in the cases of no spaces but equality, spaces are added. in the cases of spaces already, no spaces are needed therfore none are added.
-Marco Salazar
