/*
Name: Marco Salazar
Date: 4/8/18
Aggie ID: 800644204
Class: CS 271 lab10
*/
#ifndef TERM_H
#define TERM_H
#include <string>
struct term {
   int        exp;   // exponent
   double     coe;   // coefficient
   term*      next;
   term(int e, double c, term* n=0) : exp(e), coe(c), next(n) {}
};

void  release(term *t);
// free all terms pointed to by t

void  print_terms(term *t);
// print terms

std::string toString(term *t);

term* dup_terms(term *t);
// duplicate terms (copy constructor)

term* add(term *a, term *b);
// add the two polynomials a and b
// return a linked list of terms

term* subtract(term *a, term *b);
term* sub_helper(term *b);

term* build_poly(int size, double coef[], int expon[]);
// build a linked list of terms
// assume: expon[0] < expon[1] < expon[2] < ...
// if assumption is not satisfied, throw an invalid_argument exception

term* mult(term *t, double coef, int expon);
// return a new polynomial that is the result of
// multiplying the polynomial t
// with the term with coefficient "coef" and exponent "expon"


term* mult_terms(term *a, term *b);
// multiple two polynomials a and b

#endif
