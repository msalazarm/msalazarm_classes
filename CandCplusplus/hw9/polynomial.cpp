#include <iostream>
#include "term.h"
#include "polynomial.h"
using namespace std;

polynomial::polynomial(){
	h = new term(0,0, NULL);
}
polynomial::polynomial(const polynomial& p){
	(*this).h = dup_terms(p.h);
}
polynomial::polynomial(int size, double coef[], int expon[]){
	h = build_poly(size, coef, expon);
}
polynomial::~polynomial(){
	release(h);
}
void polynomial::plus(polynomial a, polynomial b){
	term* addition = add(a.h, b.h);
	(*this).h = addition;
}
void polynomial::multiply(polynomial a, polynomial b){
	term* multiplication = mult_terms(a.h, b.h);
	(*this).h = multiplication;
}
int polynomial::degree() const{
	return (*h).exp;
}
bool polynomial::isZero() const{
	return (h == NULL);
}
void polynomial::print() const{
	if(h == NULL) cout << "0\n";
	else print_terms(h);
}