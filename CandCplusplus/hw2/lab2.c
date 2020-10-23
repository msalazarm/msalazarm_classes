/*
Name: Marco Salazar
Aggie Id: 800644204
Date: 2/6/2017
class: cs271, for Lab2
*/
#include <stdio.h>
#include <string.h> //to use strlen function
#define MAX_LINE_LENGTH 100

void copy(char *, char *);
int getLine(char *, char *);
int cnt, past, c;

void main(){
	cnt = 0;
	past = 0;
	char current[MAX_LINE_LENGTH];
	char longest[MAX_LINE_LENGTH];
	while(getLine(longest, current) != EOF);
	printf("%s\n", longest);
}

int getLine(char *longest, char  *current){
	while((c = getchar()) != EOF){
		if(cnt <= 98){
			current[cnt] = c;//the current character is saved in the current array.
			if(c == '\n'){
				current[cnt + 1] = '\0';
				if(cnt > past){
					copy(longest, current);
					past = cnt;
				}
				cnt = 0;
				return past;
			}
		}
		else if(c == '\n'){//only enters this if statement if the line has more than 98 characters (the 99th is reserved for newline)
			cnt = 0;
			return 101;// if I put -1 it would exit loop in the main function so I had to not comply completely with 
				  //instructions, otherwise it would only print the longest line before ones that overun the buffer.
		}else{}
		cnt++;
	}
	//only comes here when the end of file is detected.
	cnt = 0;
	return EOF;
}//end of getLine function

void copy(char to[], char from[]){
	int temp, i;//temperary integer value and incremental i variable
	for(i = 0; from[i] != '\0'; i++){
		temp = from[i];
		to[i] = temp;
	}
	to[i] = '\0';
}//copy method transfers the current array values to the longest array
