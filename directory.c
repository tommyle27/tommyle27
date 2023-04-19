#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int main () {

	//data structure and pointers
	int bSize = 4000;
	char buffer[bSize];
	char option;
	struct dirent *ptD;
	DIR *dp;

	while (option != 'q') {

		//menu
		printf("Select the option(s) appropriately be entering the number:\n");
		printf("Enter 1 for creating a directory\n");
		printf("Enter 2 for removing directory\n");
		printf("Enter 3 for printing working directory\n");
		printf("Enter 4 for changing directory one level up\n");
		printf("Enter 5 for reading the contents of directory\n");
		printf("Enter 6 for closing the directory\n");
		printf("Enter q to exit the program\n");

		//clear input buffer; allows to accept the next string
		fflush(stdin);
		//scan input
		scanf(" %s", &option);

		//option 1 (create/name directory)
		if (option == '1') {

			char FileNameGiven[256];

			printf("Enter the Directory name you want to create:\n");
			fflush(stdin);
			scanf(" %s", FileNameGiven);

			//make directory path with given name "FileNameGiven"
			int x = mkdir(FileNameGiven, O_RDWR);

			if (x == 0) {
				printf("Directory is Created Successfully.\n");
			} else {
				printf("Directory Creation Failed.\n");
			}

		//option 2 (remove directory via typing name of directory)
		} else if (option == '2') {

			char RmvFileName[256];

			printf("Enter the Directory name you want to remove: \n");
			scanf(" %s", RmvFileName);

			//remove directory path RmvFileName
			int x = rmdir(RmvFileName);

			if (x == 0) {
				printf("Directory is removed Successfully.\n");
			} else {
				printf("Directory Removal Failed.\n");
			}

		//option 3 (print current working directory)
		} else if (option == '3') {

			//get current working directory (in buffer); if buffer empty (NULL) no directory path found
			if (getcwd(buffer, sizeof(buffer)) == NULL) {
				printf("Current Directory not found. \n");
			} else {
				printf("Current Working Directory is: %s \n", buffer);
			}

		//option 4 (move current working directory up on level)
		} else if (option == '4') {

			printf("Working Directory Before Operation: %s \n", buffer);

			//changes current directory path up one level
			int x = chdir("..");

			if (x == 0) {
				getcwd(buffer, sizeof(buffer));
				printf("Directory Changed Successfully \n");
				printf("Working Directory After Operation: %s \n", buffer);
			} else { 
				printf("Current Directory not found. \n");
			}

		//option 5 (reads content in current working directory)
		} else if (option == '5') {

			//opens directory and reads/displays all the content inside
			dp = opendir(".");
			//reads the directory and prints the contents line by line while not empty
			while ((ptD = readdir(dp)) != NULL) {
				printf("%s \n", ptD->d_name);
			}

		//option 6 (close current working directory)
		} else if (option == '6') {

			//closes the directory
			int x = closedir(dp);
			if (x == 0) {
				printf("Directory Closed Successfully. \n");
			}
			else {
				printf("Directory Close Failed. \n");
			}
		}

	}
	
//option q was chosen
return 0;
}
