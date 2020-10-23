#include <stdio.h>
#include <stdlib.h>
FILE *fpi;
/*#define EOF         -1                     */
#define OpenParen    0 
#define CloseParen   1
#define Plus         2
#define Minus        3
#define Mult         4
#define Divide       5
#define Operand      6

int get_token(int *w);
/* returns one of the eight possible integer token values as defined above.
In case the token returned is Operand, get_token also returns the
integer operand value in *w. Otherwise, *w is not defined.*/
