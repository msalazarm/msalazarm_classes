

#include "tokenizer.h"

int get_operand(int *w)
{int c;

   *w = 0; 
   while ((c = getc(fpi)) != EOF)
      if (c >= '0' && c <= '9') *w = 10*(*w) + c - 48;
      else {ungetc(c,fpi); return;} 
}

int get_token(int *w)
{
int c;

   while ((c = getc(fpi)) != EOF)
         if      ( c=='(' ) return(OpenParen);
         else if ( c==')' ) return(CloseParen);
         else if ( c=='+' ) return(Plus);
         else if ( c=='-' ) return(Minus);
         else if ( c=='*' ) return(Mult);
         else if ( c=='/' ) return(Divide);
         else if ( c>='0' && c<='9' ) 
                            {ungetc(c,fpi);get_operand(w);return(Operand);}
         else if ( c>=33 && c<=126 ) 
                            {printf("\nnot a token; program aborts\n"); exit(1);}

   return(EOF);
}

