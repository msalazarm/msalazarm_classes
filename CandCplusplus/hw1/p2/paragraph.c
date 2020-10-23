/*
Name: Marco Salazar
Aggie ID: 800644204
Date: 1/28/2018
Assignment: Homework/lab #1, problem 2.
CS 271 M01
*/
#include<stdio.h>

void main(){
	int ch;
	int newline = 0;
	int spaces = 0;
	int wasNewline = 0;
	while ((ch = getchar()) != EOF) {
		if((ch >=33 && ch <= 126) || ch == 10 || ch == 9){
			if(ch == 10){
				if(wasNewline == 1){
					spaces = 0;
				}
				newline++;
				wasNewline = 1;
				if(newline > 1){
					if(newline ==2) putchar(ch);
					continue;
				}
				putchar(ch);
				continue;
			}
			for(; spaces > 0; spaces--) putchar(32);
			newline = 0;
			putchar(ch);
		}
		if(ch <= 32 || ch > 126){
			spaces++;
		}
	}
}
