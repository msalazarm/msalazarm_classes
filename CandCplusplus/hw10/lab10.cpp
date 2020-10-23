/*
Name: Marco Salazar
Date: 4/8/18
Aggie ID: 800644204
Class: CS 271 lab10
*/
#include "polynomial.h"
#include <iostream>
#include <stdexcept>
using namespace std;

main() {
   double coe1[4] = {1,   2,  3,  4};
   double coe2[4] = {-1, -2, -3, -4};
   int    exp1[4] = {0,   4, 14, 18};
   int    exp2[4] = {0,  14,  4, 18};

   polynomial p(4,coe1,exp1), q(4,coe2,exp1), s;

   cout << "P(x)        = ";
   p.print();
   cout << "Q(x)        = ";
   q.print();
   s.plus(q,q);
   cout << "Q(x) + Q(x) = ";
   s.print();
   s.plus(p, q);
   cout << "P(x) + Q(x) = ";
   s.print();
   s.multiply(p, p);
   cout << "P(x) * P(x) = ";
   s.print();
   cout << endl;

   cout << "print the p and q polynomials with the overloaded << symbol: \n";
   cout << "p: " << p << "\tq: " << q << endl << endl;
   cout << "p + p with overloaded expressions: " << (p + p) << endl << endl;
   cout << "q * p with overloaded expressions: " << (p * q) << endl << endl;
   polynomial temp = polynomial();
   cout << "s printed: " << s << endl;
   s = temp;
   cout << "an empty polynomial is assigned (=) to s.\ns printed: " << s << endl;
   s = s;
   cout << "There can be no self assignment s = s gives: " << s << endl << endl;
   cout << "p - q with overloaded expressions: " << (p - q) << endl;
   cout << "p - p with overloaded expressions: " << (p - p) << endl << endl;
   s = p;
   s += p;
   cout << "assigning p to s, then s += p with overloaded expressions: " << s << endl << endl;
   s = p;
   s -= p;
   cout << "assigning p to s, then s -= p with overloaded expressions: " << s << endl << endl;
   s = p;
   s *= p;
   cout << "assigning p to s, then s *= p with overloaded expressions: " << s << endl;
}

