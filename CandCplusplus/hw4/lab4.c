/*
Name: Marco Salazar
Class: CS271 lab4
Date: 2/25/18
Aggie ID: 800644204

PLEASE READ README
*/
#include "tokenizer.h"

int  eval_expr();
int  eval_expr_1(int opn1);
int  eval_expr_2(int opn1,int opr1);
int  eval_expr_3(int opn1,int opr1, int opn2);
int  eval_expr_4(int opn1,int opr1, int opn2, int opr2);

void error(int i) {fprintf(stderr, "error: %d\n", i); exit(i);}

void main(int argc, char *argv[])
{
   int w, val;
   fpi = fopen( *++argv, "r" );
   if (get_token(&w)!=OpenParen) error(-1);
   val =  eval_expr();
   if (get_token(&w)!=EOF) error(-2);
   printf("expression evaluated to %d\n", val);
}

int eval_expr()
/* have seen

        (

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{
    int w;
    switch (get_token(&w))
    {
      case OpenParen:
           return eval_expr_1(eval_expr());
      case CloseParen:
           error(2);
      case Plus:
           error(3);
      case Minus:
           error(4);
      case Mult:
           error(5);
      case Divide:
           error(6);
      case Operand:
           return eval_expr_1(w);
      case EOF:
           error(7);
    }
}

int eval_expr_1(int opn1)
/* have seen

        ( opn1

   where opn1 is an operand

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{
    int w;
    switch (get_token(&w))
    {
      case OpenParen:
           error(8);
      case CloseParen:
           return opn1;
      case Plus:
           return eval_expr_2(opn1, Plus);
      case Minus:
           return eval_expr_2(opn1, Minus);
      case Mult:
           return eval_expr_2(opn1, Mult);
      case Divide:
           return eval_expr_2(opn1, Divide) ;
      case Operand:
           error(10);
      case EOF:
           error(11);
    }
}

int eval_expr_2(int opn1,int opr1)
/* have seen

        ( opn1 opr1

   where opn1 is an operand
     and opr1 is an operator

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{
    int w;
    switch (get_token(&w))
    {
      case OpenParen:
           return  eval_expr_3(opn1, opr1, eval_expr());
      case CloseParen:
           error(12);
      case Plus:
           error(13);
      case Minus:
           error(14);
      case Mult:
           error(15);
      case Divide:
           error(16);
      case Operand:
           return eval_expr_3(opn1, opr1, w);
      case EOF:
           error(17);
    }
}


int eval_expr_3(int opn1,int opr1, int opn2)
/* have seen

        ( opn1 opr1 opn2

   where opn1 and opn2 are operands,
         opr1 is an operator

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{
    int w;
    switch (get_token(&w))
    {
      case OpenParen:
           error(18);
      case CloseParen:
           switch (opr1)
           {
             case Plus:   return (opn1 + opn2);
             case Minus:  return (opn1 - opn2);
             case Mult:   return (opn1 * opn2);
             case Divide: return (opn1 / opn2);
           }
      case Plus:
           switch (opr1)
           {
             case Plus:   return eval_expr_2((opn1 + opn2), Plus);
             case Minus:  return eval_expr_2((opn1 - opn2), Plus);
             case Mult:   return eval_expr_2((opn1 * opn2), Plus);
             case Divide: return eval_expr_2((opn1 / opn2), Plus);
           }
      case Minus:
           switch (opr1)
           {
             case Plus:   return eval_expr_2((opn1 + opn2), Minus);
             case Minus:  return eval_expr_2((opn1 - opn2), Minus);
             case Mult:   return eval_expr_2((opn1 * opn2), Minus);
             case Divide: return eval_expr_2((opn1 / opn2), Minus);
           }
      case Mult:
           switch (opr1)
           {
             case Plus:   return (opn1 + eval_expr_2(opn2, Mult));
             case Minus:  return (opn1 -eval_expr_2(opn2, Mult));
             case Mult:   return eval_expr_2((opn1 * opn2), Mult);
             case Divide: return eval_expr_2((opn1 / opn2), Mult);
           }
      case Divide:
           switch (opr1)
           {
             case Plus:   return (opn1 + eval_expr_2(opn2, Divide));
             case Minus:  return (opn1 - eval_expr_2(opn2, Divide));
             case Mult:   return eval_expr_2((opn1 * opn2), Divide);
             case Divide: return eval_expr_2((opn1 / opn2), Divide);
           }
      case Operand:
           error(20);
      case EOF:
           error(21);
    }
}

/*
		PLEASE READ README FOR THE REASON THAT I DID NO USE eval_expr_4()
*/
int eval_expr_4(int opn1, int opr1, int opn2, int opr2)
 /*have seen

        ( opn1 opr1 opn2 opr2

   where opn1 and opn2 are operands,
         opr1 and opr2 are operators

   read until we find a matching parenthesis.
   the expression enclosed is evaluated.
   return the integer value computed.
*/
{
    int w;
    switch (get_token(&w))
    { case OpenParen:
           switch (opr2)
           {
             case Mult:   return eval_expr_3(opn1, opr1, opn2 * eval_expr()) ;
             case Divide: return eval_expr_3(opn1, opr1, opn2 / eval_expr()) ;
           }
      case CloseParen:
           error(22);
      case Plus:
           error(23);
      case Minus:
           error(24);
      case Mult:
           error(25);
      case Divide:
           error(26);
      case Operand:
           switch (opr2)
           {
             case Mult:   return eval_expr_3(opn1, opr1, opn2 * w) ;
             case Divide: return eval_expr_3(opn1, opr1, opn2 / w) ;
           }
      case EOF:
           error(27);
    }
}