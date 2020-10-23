
#ifndef REGEXP_H
#define REGEXP_H

#include <cassert>

enum expType {empty_set,empty_string,literal,concat,alt,kleene_star};

class regExp {

public:

   regExp():                 type(empty_set), e(0), e1(0), empty(false) {}

   regExp(const char* s):    type(empty_string),e(0), e1(0),empty(true)  
                             {assert(*s=='\0');}

   regExp(char x):           type(literal),c(x),e(0),e1(0),empty(false) 
                             {assert('a'<=x && x<='z');}

   regExp(const regExp& r):  type(r.type),c(r.c), e(r.e?r.e->dup():0),
                             e1(r.e1?r.e1->dup():0),empty(r.empty) {} 

  ~regExp()                  {destroyHelper(e); destroyHelper(e1);}

   const regExp& operator=(const regExp &r); // assignment operator

   regExp& operator++(int);        // Kleene star   operator             
   regExp& operator^(regExp& r);   // concatenation operator   
   regExp& operator|(regExp& r);   // alternation   operator

   void print() const;

   bool isEmptyStr()         {return type==empty_string;}
   bool isChar()             {return type==literal;}
   char chr()                {assert(isChar()); return c;}

private:

   expType type;
   char    c;       
   regExp  *e, *e1;       // component expressions
   bool    empty;         // true iff regular expression recognizes empty string


   // private constructor; not for public use.
   // constructor for expType 'concat', 'alt' or 'kleene_star'.
   //
   // that is,
   //    assert(type==concat || type==alt || type==kleene_star)
   //
   // r and r1 are the component expressions.
   // just use r and r1 directly in the construction of a new regExp.
   // no need to do copying (deep or shallow) of r or r1.
   //
   regExp(expType t, regExp *r = 0, regExp *r1 = 0); 

   // return a deep copy of this object
   regExp* dup();          

   // destruct r recursively
   void destroyHelper( regExp *r );
};

#endif
