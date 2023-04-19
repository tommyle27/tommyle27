/*
--------------------------------------------------
Project: cp264-a1q1
File:    caseflip.c
Author:  Tommy Le
Version: 2022-01-13
--------------------------------------------------
*/
#include <stdio.h>

int main() {
	//the following two lines are for Eclipse console none-buffered output, in can you use Eclipse to do your assignment
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char c = 0, temp;

	do {
		//input character
		printf("Please enter a character \n");
		scanf("%c", &c); //this is to get a character input from keyboard


		//flush the input buffer
		do { //gets rid of additional characters in stdin buffer
			scanf("%c", &temp);
			if(temp=='\n') break;

		} while(1);
		//process input character
		// code here
		if (c>= 'a' && c <= 'z') {
			printf("%c:%d,%c \n", c, c, c-32);
		} else if(c >= 'A' && c <= 'Z') {
			printf("%c:%d,%c \n", c, c, c+32);
		} else if (c >= '0' && c <= '9') {
			int x = c - '0';
			printf("%c:%d,%d \n", c, c, x*x);
		} else  if (c == '*'){
			break;
		} else {
			printf("%c:invalid \n", c);
		}


	} while (1);
	printf("%c:quit\n", c);

	return 0;
}

