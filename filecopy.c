#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//define buffer size
#define bSize 4000

/*
argument counter and argument vector set as parameters, where argc stores number of
command line arguments and program names, and argv is an array of char pointers
listing the arguments 
*/
int main(int argc, char *argv[]) {

	//argc cannot be lesser than 3 since values passed will be make argc a greater value
	if (argc < 3) {
		printf("Insufficient parameters passed. \n");
		exit(0);
	}

	//data structure
	int input, output;
	char buffer[bSize];

	/*assigns input a value of -1 or 0 if file (argv[1]) can be accessed and 
	reading permission is granted (R_OK), if it can input == 0 else input == -1*/
	input = access(argv[1], R_OK);

	//file is accessed
	if (input == 0) {

		// opens for reading 
		input = open(argv[1], O_RDONLY);
		//creates output file if it doesn't exist for reading and writing
		output = open(argv[2], O_CREAT | O_RDWR);

		//if file exists/accesible
		if (input != -1) {

			//non-negative value n type size_t, reads data from buffer of byte length sizeof(buffer)-1 in input file
			size_t n = read(input, buffer, sizeof(buffer)-1);

			//writes data into output file
			write(output, buffer, n);
			close(output);
			close(input);
			printf("The contents of file 'input.txt' have been successfully copied into 'output.txt' file \n");

		} else {
			printf("Error: Cannot read input file \n");
		}
	}
return 0;
}
