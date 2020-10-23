#include "tokenizer.h"
void main(int argc, char *argv[]){
	int token, opn;

	fpi = fopen( *++argv, "r" );
	while ( (token = get_token(&opn)) != EOF )
		switch (token) {
			case OpenParen:
				printf("(\n");
				break;
			case CloseParen:
				printf(")\n");
				break;
			case Plus:
				printf("+\n");
				break;
			case Minus:
				printf("-\n");
				break;
			case Mult:
				printf("*\n");
				break;
			case Divide:
				printf("/\n");
				break;
			case Operand:
				printf("Operand: %d\n", opn);
		}
}

