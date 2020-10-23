#include <iostream>
#include "regExp.h"
using namespace std;

main() {

// example taken from Ex. 1.68 from page 76 of 
// Introduction to theory of computation (by Michael Sipser)

// state 0 is not used
// state 4 is the new start  state s
// state 5 is the new accept state a

regExp t[6][6];            // by default constructor, each is an emptySet regExp

int n = 3;  

   t[4][1] = regExp("");                       // epsilon transition from s -> 1
   t[2][5] = regExp("");                       // epsilon transition from 2 -> a
   t[3][5] = regExp("");                       // epsilon transition from 3 -> a

   t[1][2] = t[2][1] = t[3][2] = regExp('a');     
   t[1][3] = t[3][1] = t[2][2] = regExp('b');

   for (int j=1; j<=n; j++)                    // remove state j
       for (int i=j+1; i<=n+2; i++)            
       for (int k=j+1; k<=n+2; k++) 
           t[i][k] =  t[i][j] ^ t[j][j]++ ^ t[j][k] | t[i][k];
   
   t[n+1][n+2].print(); 
   cout << endl;
}

/* outputs:

((a(aa|b)*ab|b)((ba|a)(aa|b)*ab|bb)*((ba|a)(aa|b)*|1)|a(aa|b)*)

*/
