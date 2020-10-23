#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

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

   void multiply(polynomial a, polynomial b);           
   // multiply two polynomials

   int  degree() const;                                 
   // returns degree of polynomial

   bool isZero() const;                                 
   // true if the polynomial is a zero polynomial
   // false otherwise

   void print()  const;                                 
   // print a polynomial 

private:
   term*   h;

};

#endif
