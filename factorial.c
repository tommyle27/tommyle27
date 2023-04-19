/*
--------------------------------------------------
Project: cp264-a1q1
File:    caseflip.c
Author:  Tommy Le
Version: 2022-01-13
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *args[]) {
	int i, n = 0, f = 1, prev, is_pverflow = 0;
	printf("factorial \n");
	scanf("%d", &i);

	if(argc > 1) {
		n = atoi(args[1]); // convert command line argument to an int

		if (n>=1) { // the conversion is successful
			// code here
			for(prev = 1; prev <= i; prev++) {
				f *= prev;

				if (prev == 4) {
					printf("%11d \n", f);
				} else if (prev >= 13){
					printf("overflow:13!");
				} else {
					printf("%11d", f);
				}
			}

		} else {
			printf("%s:invalid argument \n", args[1]);
		}
	} else {
		printf("no argument");
	}
	return 0;
}

