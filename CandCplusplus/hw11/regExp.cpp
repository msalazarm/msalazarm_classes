#include "regExp.h"
#include <iostream>
#include <string>
using namespace std;

const regExp& regExp::operator=(const regExp &r){
	regExp* result = new regExp();
	if(this == &r){return r;}
	type  = r.type;
	c     = r.c;
	empty = r.empty;
	e1    =(r.e1)->dup();
	e     =(r.e)->dup();
	return (*this);
}

regExp& regExp::operator++(int x){
	regExp* result;
		 if(type == empty_set)   {return *new regExp("");								   }
	else if(type == empty_string){return *new regExp("");								   }
	else if(type == kleene_star) {return *new regExp(*this);							   }
	else                         {return *new regExp(kleene_star, new regExp(*this), NULL);}
}

regExp& regExp::operator^(regExp& r){
	regExp* result;
	if     (r.type == empty_string){return *new regExp(*this); 									 }
	else if(type == empty_string)  {return *new regExp(r);             							 }
	else if(r.type == empty_set)   {return *new regExp();										 }
	else if(type == empty_set)     {return *new regExp(); 										 }
	else						   {return *new regExp(concat, new regExp(*this), new regExp(r));}
}

regExp& regExp::operator|(regExp& r){
	regExp* result;
	if     (type == empty_set)	{return *new regExp(r);                					   }
	else if(r.type == empty_set){return *new regExp(((regExp)*this));					   }
	else						{return *new regExp(alt, new regExp(*this), new regExp(r));}
}

void regExp::print() const{
	if(this == NULL) return;
	else if(type == empty_set)    cout << "0";
	else if(type == empty_string) cout << "1";
	else if(type == literal)      cout << c;
	else if(type == concat)		{			   e->print();              e1->print();             }
	else if(type == alt)		{ cout << "("; e->print(); cout << "|"; e1->print(); cout << ")";}
	else if(type == kleene_star){
		if(e->type == alt)		 {			   e->print(); cout << "*";                         }
		else              		 {cout << "("; e->print(); cout << ")*";                        }}
}

regExp::regExp(expType t, regExp *r, regExp *r1){
	type=t; e=r; e1=r1;
	empty = (type==concat ? r->empty & r1->empty: type==alt ? r->empty || r1->empty :true);
	assert(type == concat || type == alt || type == kleene_star);
}

regExp* regExp::dup(){
	regExp* result = new regExp();
	if(this == NULL) return NULL;
	else{
		result->type = type;
		result->c = c;
		result->empty = empty;
		if(e != NULL) result->e = new regExp(*e);
		else result->e = NULL;
		if(e1 != NULL)result->e1 =new regExp(*e1);
		else result->e1 = NULL;
	}
}

void regExp::destroyHelper(regExp *r){
	if(r == NULL) return;
	else{
		destroyHelper(r->e);
		destroyHelper(r->e1);
		delete r;
	}
}