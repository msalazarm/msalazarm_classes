/*
Name: Marco Salazar
Date: 4/8/18
Aggie ID: 800644204
Class: CS 271 lab10
*/
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
#include "term.h"

class polynomial {

public:
   polynomial();
   // default constructor

   polynomial(const polynomial& p);
   // copy constructor

   polynomial(int size, double coef[], int expon[]);
   // constructor
   // assume: expon[0] < expon[1] < expon[2] < ...
   // if assumption is not satisfied, throw an invalid_argument exception

   ~polynomial();
   // destructor

   void plus(polynomial a, polynomial b);
   // add two polynomials

   void minus(polynomial a, polynomial b);

   void multiply(polynomial a, polynomial b);
   // multiply two polynomials

   int  degree() const;
   // returns degree of polynomial

   bool isZero() const;
   // true if the polynomial is a zero polynomial
   // false otherwise

   void print()  const;
   // print a polynomial

   polynomial &operator=(polynomial &poly2);
   polynomial operator+(polynomial poly2);
   polynomial operator-(polynomial poly2);
   polynomial operator*(polynomial poly2);
   void operator+=(polynomial poly2);
   void operator-=(polynomial poly2);
   void operator*=(polynomial poly2);
   friend std::ostream &operator<<(std::ostream &, const polynomial &);


private:
   term*   h;

};

#endif
