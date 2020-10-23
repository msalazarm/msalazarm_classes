#include <iostream>
#include "term.h"
using namespace std;

void  release(term *t)
{
	if(t != NULL) release((*t).next);
	delete t;
}
void print_terms(term *t){
	if(t != NULL){
		if(t->exp != 0) cout << t->coe << "x^" << t->exp;
		else cout << t->coe;
		if((*t).next != NULL) cout << " + ";
		print_terms((*t).next);
	}else{
		cout << endl;
	}
}
term* dup_terms(term *t){
	if(t == NULL) return NULL;
	else if(t->next == NULL){
		term* copy = new term((*t).exp, (*t).coe, NULL);
		return copy;
	}
	else{
		term* copy = new term((*t).exp, (*t).coe, dup_terms((*t).next));
		return copy;
	}
}
term* add(term *a, term *b){
	if(!a) return dup_terms(b);
	if(!b) return dup_terms(a);
	if((*a).exp > (*b).exp) return new term((*a).exp, (*a).coe, add((*a).next, b));
	if((*a).exp < (*b).exp) return new term((*b).exp, (*b).coe, add(a, (*b).next));
	if((*a).coe + (*b).coe) return new term((*a).exp, (*a).coe + (*b).coe, add((*a).next, (*b).next));
	return add((*a).next, (*b).next);
}
term* build_poly(int size, double coef[], int expon[]){
	term* poly;
	if(!size){
		return NULL;
	}else{
		poly = new term(expon[size-1], coef[size-1], build_poly(size-1, coef, expon));
	}
	return poly;
}
term* mult(term *t, double coef, int expon){
	term* result = new term((*t).exp + expon, coef * (*t).coe, NULL);
	return result;
}
term* mult_terms(term *a, term *b){
	term* atemp; term* btemp;
	term* anext; term* bnext;
	term* temp = NULL;
	if(a == NULL || b == NULL) return NULL;
	for(anext = dup_terms(a); anext != NULL; anext = (*anext).next){
		for(bnext = dup_terms(b); bnext != NULL; bnext = (*bnext).next){
			temp = add(temp, mult(anext, bnext->coe, bnext->exp));
		}
	}
	return temp;
}