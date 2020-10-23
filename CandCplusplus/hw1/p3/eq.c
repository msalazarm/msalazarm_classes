/*
//Name: Marco Salazar
//Aggie ID: 800644204
//Date: 1/28/2018
//Assignment: Homework/Lab #1, problem 3
//CS 271 M01
//description: same as problem 2, but it smartly puts spaces around =, ==, and !=. only if it makes sense and two things are actually being put together for tests of equality.
*/
#include<stdio.h>

void reset();

static int array[6] = {0,0,0,0,0,0};

void main(){
	int ch;
	int newline = 0;
	int spaces = 0;
	int wasNewline = 0;
	while ((ch = getchar()) != EOF) {
		if((ch >=33 && ch <= 126) || ch == 10 || ch == 9){
			if(ch == 10){
				reset(); //if there is a newline, there is no possibility of an equality
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
			if(ch == 9) reset(); //if anytime there is a tab, there is no possibility of equality
			for(; spaces > 0; spaces--) putchar(32);
			newline = 0;
			// if ch is either ! or =, and array0 is not nothing, tab, newline; and is readable:
			if((ch == 61 || ch == 33) && (array[0] >= 33 && array[0] <= 126) && (array[0] != 33 && array[0] != 61)){
				if(array[1] == 32){array[2] = ch; array[3] = getchar(); //putspaceforold
					putchar(array[2]);// _ +???
					if(array[3] == 10){ newline++; putchar(10); reset(); continue;} //if newline, reset and prin
				   else if(array[3] == 9) {            putchar(9);  reset(); continue;} //tab reset
				   else if(array[3] == 61){            putchar(61); array[4] = getchar(); // _ +=??
						if(array[4] == 10)                   { newline++;   putchar(10);       reset(); continue;} //newline reset
					   else if(array[4] == 9)                    {              putchar(9);        reset(); continue;} //tab reset
					   else if(array[4] >= 33 && array[4] <= 126){ putchar(32); putchar(array[4]); reset(); array[0] = 1; continue;} //done
						else                                 {              putchar(32);       reset(); array[0] = 1; continue;} //otherwise it is a space anyways so who cares
					}
					else if(array[3] >= 33 && array[3] <=126){                       // _ +3??
						if(array[2] == 33){             putchar(array[3]); reset(); array[0] = 1; continue;}
						else              {putchar(32); putchar(array[3]); reset(); array[0] = 1; continue;}
					}
					else{ //is a space
						if(array[2] == 33){ putchar(32); reset(); continue;}  // _ ! ??
						else              { putchar(32); array[4] = getchar();// _ = ??
							if(array[4] == 10){newline++; putchar(10); reset(); continue;}
						   else if(array[4] == 9 ){           putchar(9);  reset(); continue;}
						   else if(array[4] >= 33 && array[4] <= 126){putchar(array[4]); reset(); array[0] = 1; continue;}
						      else{putchar(32); reset(); continue;}
						}
					}
				}
				else{ array[1] = 0; array[2] = ch; array[3] = getchar();
					if(array[2] == 61){ //is an equal sign _=???
						if(array[3] == 10){ newline++; putchar(array[2]); putchar(10); reset(); continue;}
					   else if(array[3] == 9 ){            putchar(array[2]); putchar(9);  reset(); continue;}
					   else if(array[3] == 61){ array[4] = getchar();//is another equal sign  _==??
							if(array[4] == 10){newline++; putchar(array[2]); putchar(array[3]); putchar(10); reset(); continue;}
						   else if(array[4] == 9 ){           putchar(array[2]); putchar(array[3]); putchar(9);  reset(); continue;}
						   else if(array[4] >= 33 && array[4] <= 126){ putchar(32); putchar(array[2]);// _1==2?
								      putchar(array[3]); putchar(32); putchar(array[4]); reset(); array[0] = 1; continue;// done!
							}
						      else{         array[5] = getchar();                           //is space    _==4?
								if(array[5] == 10){newline++; putchar(array[2]); putchar(array[3]); putchar(32); putchar(10); reset(); continue;}
							   else if(array[5] == 9 ){           putchar(array[2]); putchar(array[3]); putchar(32); putchar(9); reset(); continue;}
							   else if(array[5] >= 33 && array[5] <= 126){        putchar(32); putchar(array[2]);//done!
									putchar(array[3]); putchar(32); putchar(array[5]); reset(); array[0] = 1; continue;
								}
							      else{putchar(array[2]); putchar(array[3]); putchar(32); putchar(32); reset(); continue;}
							}
						}                                       //is a character _=_??
					   else if(array[3] >= 33 && array[3] <= 126){putchar(32); putchar(array[2]); putchar(32); 
										      putchar(array[3]); reset(); array[0] = 1; continue;//done!
						}
					      else{array[4] = getchar();                //is space      _=3??
							if(array[4] == 10){newline++; putchar(array[2]); putchar(32); putchar(10); reset(); continue;}
						   else if(array[4] == 9 ){           putchar(array[2]); putchar(32); putchar(9);  reset(); continue;}
						   else if(array[4] >= 33 && array[4] <= 126){putchar(32); putchar(array[2]); putchar(32);
										      putchar(array[4]); reset(); array[0] = 1; continue;//done!
							}
						      else{putchar(array[2]); putchar(32); putchar(32);  reset(); continue;}
						}
					}
					else{               // is a ! point    _1!???
						if(array[3] == 10){ newline++; putchar(array[2]); putchar(10); reset(); continue;}
					   else if(array[3] == 9 ){            putchar(array[2]); putchar(9);  reset(); continue;}
					   else if(array[3] == 61){array[4] = getchar(); // is an equal _1!=??
							if(array[4] == 10){newline++; putchar(array[2]); putchar(array[3]); putchar(10); reset(); continue;}
						   else if(array[4] == 9 ){           putchar(array[2]); putchar(array[3]); putchar(9); reset(); continue;}
						   else if(array[4] >= 33 && array[4] <= 126){putchar(32); putchar(array[2]); putchar(array[3]);
								putchar(32); putchar(array[4]); reset(); array[0] = 1; continue;}//done!
						      else{array[5] = getchar();                // is a space  _1!= ?
								if(array[5] == 10){putchar(array[2]); putchar(array[3]); putchar(32); putchar(10); reset(); continue;}
							   else if(array[5] == 9 ){putchar(array[2]); putchar(array[3]); putchar(32); putchar(9); reset(); continue;}
							   else if(array[5] >= 33 && array[5] <= 126){putchar(32); putchar(array[2]);//done!
									putchar(array[3]); putchar(32); putchar(array[5]); reset(); array[0] = 1; continue;
								}
							      else{putchar(array[2]); putchar(array[3]); putchar(32); putchar(32); reset(); continue;}
							}
						}
					   else if(array[3] >= 33 && array[3] <= 126){putchar(array[2]); putchar(array[3]); reset(); array[0] = 1; continue;}
					      else{putchar(array[2]); putchar(32); reset(); continue;}
					}
				}
			}
			else{
				if((ch == 61 || ch == 33) ) reset();
			}
			putchar(ch);
			reset();//make reset for tab exclisive to go back
			array[0] = ch;
		}
		if(ch <= 32 || ch > 126){
			//if array0 is readable, not newline, not nothing, and not tab: array1 can become a space
			if(array[0] != 0 && (array[0] >= 33 && array[0] <= 126)) array[1] = 32;
			else {reset(); }
			spaces++;
		}
	}
}

void reset(){
	array[0] = 0;
	array[1] = 0;
	array[2] = 0;
	array[3] = 0;
	array[4] = 0;
	array[5] = 0;
}
