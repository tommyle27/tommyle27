#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

/*
Authors: Tommy Le (200298530), Vyren Patel (200669700)
Date: 2023-02-09
*/

int main () {

	int grades[10][6]; //grade array for 10 students & 6 assignments
	int TA[6]; //array of assignments/grades
    int std = 0, grd = 0;

	FILE* file = fopen("sample_in_grades.txt","r");

    if (file == NULL) {
        perror("Failure to open file.");
        return -1;
    }

    //while loop reads through file, content to grades array
	while (1) {

        //if end of file break out of loop
        if (feof(file)) {
            break;
        }

		grd = 0;
		fscanf(file, "%d %d %d %d %d %d", &grades[std][grd], &grades[std][grd+1], 
        &grades[std][grd+2], &grades[std][grd+3], &grades[std][grd+4], &grades[std][grd+5]);

		std++;
	}

    //for loop TA process, finds sum of marks of all 6 assignments
	for (int tempGr = 0; tempGr < 6; tempGr++) {

		TA[tempGr]=0;

		for (std = 0; std < 10; std++) {
			TA[tempGr] += grades[std][tempGr];
        }

	}

    //for loop, finds average of assignments and prints average
	for (grd = 0; grd < 6; grd++) {

		float avg = (float)TA[grd]/10;
		printf("A s s i g n m e n t  %d  -  A v e r a g e  =  %.6f\n", grd+1, avg);
	}

    //closes file
    fclose(file);

	return 0;
}