/*
Name: Marco Salazar
Date: 4/8/18
Aggie ID: 800644204
Class: CS 271 lab10
*/
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
void polynomial::minus(polynomial a, polynomial b){
	term* sub = subtract(a.h, b.h);
	(*this).h = sub;
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
polynomial &polynomial::operator=(polynomial &poly2){
	if(&poly2 != this){
		this->h = dup_terms(poly2.h);
	}
	return *this;
}
polynomial polynomial::operator+(polynomial poly2){
	polynomial result = polynomial();
	result.h = add(h, poly2.h);
	return result;
}
polynomial polynomial::operator-(polynomial poly2){
	polynomial result = polynomial();
	result.h = subtract(h, poly2.h);
	return result;
}
polynomial polynomial::operator*(polynomial poly2){
	polynomial result = polynomial();
	polynomial temp = polynomial(poly2);
	polynomial thi = polynomial(*this);
	result.multiply(thi, temp);
	return result;
}
void polynomial::operator+=(polynomial poly2){
	polynomial result = polynomial();
	polynomial temp = *this;
	result.h = add(temp.h, poly2.h);

	*this = result;
}
void polynomial::operator-=(polynomial poly2){
	polynomial result = polynomial();
	polynomial temp = *this;
	result.h = subtract(temp.h, poly2.h);

	*this = result;
}
void polynomial::operator*=(polynomial poly2){
	polynomial result = polynomial();
	polynomial temp = *this;
	result.multiply(temp, poly2);
	*this = result;
}
ostream &operator<<(ostream &output, const polynomial &p){
	if(p.h == NULL){ output << "0"; return output;}
	else{
		string result = toString(p.h);
		output << result;
	}
	return output;
}