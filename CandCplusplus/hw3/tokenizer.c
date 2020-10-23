//Name:Marco Salazar
//Class: CS 271 lab 3
//Date: 2/17/18
//AggieID: 800644204
#include "tokenizer.h"

int get_token(int * w){
	int c;
	*w= 0;
	int i = 0;
	while(1){
	c = fgetc(fpi);
	if(c == 40) return OpenParen;
	if(c == 41) return CloseParen;
	if(c == 43) return Plus;
	if(c == 45) return Minus;
	if(c == 42) return Mult;
	if(c == 47) return Divide;
	if(c == EOF) return EOF;
	if(c == 32 || c == 10 || c == 9) continue;//if space tab or newline restart function

	if(c >= 48 && c <= 57){
		for(; c >= 48 && c <= 57; c = fgetc(fpi)){
			*w = (*w)*10 + c-48;
		}
		ungetc(c, fpi);
		return Operand;
	}

	if(c >=33 && c <= 126){
		printf("not a token; program aborts");
		exit(1);
	}
	}
}
