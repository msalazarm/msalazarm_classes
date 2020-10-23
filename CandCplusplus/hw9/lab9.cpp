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

   try
   {
      polynomial r(4,coe1,exp2);
   }
   catch (invalid_argument &e)
   {
      cout << "Exception: " << e.what() << endl;
   }
}

/* outputs:

P(x)        =   4x^18 +  3x^14 +  2x^ 4 +  1
Q(x)        =  -4x^18 + -3x^14 + -2x^ 4 + -1
Q(x) + Q(x) =  -8x^18 + -6x^14 + -4x^ 4 + -2
P(x) + Q(x) =   0
P(x) * P(x) =  16x^36 + 24x^32 +  9x^28 + 16x^22 + 20x^18 +  6x^14 +  4x^ 8 +  4x^ 4 +  1

Exception: exponents are not in increasing order

*/
