#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/*
Authors: Tommy Le (200298530), Vyren Patel (200669700)
Date: 2023-02-09
*/

#define SMMAX 4096 //max size for sharedMem memory
#define BUFFMAX 4096

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Insufficient parameters passed. \n");
		exit(1);
	}

	//create sharedMem memory
	int sharedMem = shm_open("sharedMem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); 

	//set size to sharedMem and checks if it worked
	if (ftruncate(sharedMem, SMMAX) == -1) {  
		perror("Memory Size error");
		exit(1);
	}

	//create memory mapped file and pointer used to access shared memory
	char *mem = mmap(NULL, SMMAX, PROT_READ | PROT_WRITE, MAP_sharedMem, sharedMem, 0); 
	//check if there are no adresses created
	if (mem == MAP_FAILED) { 
		perror("Memory map error");
		exit(1);
	}

 	//creates child process, value returned from fork() will be stored in pid1
	pid_t pid1;
	pid1 = fork();

	//In child process
	if (pid1 == 0) {

		FILE* file = fopen(argv[1], "r");

		//error to open file
		if (file == ((void *)0)) {
			exit(1);
		}

		//reads data from file
		int wread = fread(mem , 1 , SMMAX, file);

		//error in reading content
		if (wread == 0) {
			exit(1);
		}
		//add NULL
		mem[wread] = '\0';
		

	} else if (pid1 > 0) {
		int stat;
		wait(&stat);

		//checks if child termininated normally
		if (WIEXITED(out)) {

			//checks exit status of child
			if (WEXITSTATUS(out) == -1) {
				perror("Error\n");
				exit(1);
			} else { 
				perror("Error\n"); 
				exit(1);
			}

	} else {
		fprintf(stdout, "Unable to create a child process! \n");
		perror("Fork");
		exit(0);
	}

	int lines = 0;
	int i = 0;

	//while not NULL, check if there's a new line
	while (mem[i] != '\0') {

		if (mem[i] == '\n') {
			lines++;
		}
		i++;
	}

	//ensure no new line at the end of the file
	if (i > 0 && mem[i - 1] == '\n') { 
		mem[i - 1] = '\0';
		lines--;
	}

	//n new lines = n+1 lines
	lines++;
	//create array with size
	char** cmd = malloc(sizeof(char*) * lines); 
	int set = 0;

	for (i = 0; i < lines; i++) {
		//add duplicate value to array
		cmd[i] = strdup(mem + set);
		//update set by one extra for NULL value 
		set += strlen(cmd[i]) + 1; 
	}

	//unmap the memory
	munmap(mem , SMMAX);
	//close the sharedMem memory 
	close(sharedMem); 

	//done with child 1
	//buffMem to store child output
	char* buffMem = malloc(sizeof(char) * 4096); 

	//for each child
	for (i = 0; i < lines; i++) { 

		//parse the cmd
		char* newcmd = strdup(cmd[i]); 

		argc = 0;
		int len = strlen(newcmd);

		//find new number of arguments
		for (int i = 0; i < len; i++) { 
			
            if (newcmd[i] == ' ') {
				newcmd[i] = '\0';
				argc++;
			}
		}

		argc++;
		//create pointer
		char* newArgs[argc + 1];
		set = 0;

		for (i = 0; i < argc; i++) {
			newArgs[i] = newcmd + set;
			set += strlen(newArgs[i]) + 1;
		}

		//last character to NULL
		newArgs[argc] = NULL; 
		//create pipe
		int piper[2]; 

		//check for error in creating
		if (pipe(piper) == -1) { 
			perror("Pipe error");
			exit(1);
		}

		pid_t pid2;
		pid2 = fork();

		if (pid2 == 0) {
			//close read end of pipe
			close(piper[0]); 

			//check for error when dup
			if (dup2(piper[1], STDOUT_FILENO) == -1) { 
				perror("error in dup2");
				exit(1);
			}

			execvp(newArgs[0] , newArgs);
		}

		//in parent
		close(piper[1]); 
		//wait for child to finish
		wait(NULL); 

		//output of pipe as string
		int reader = read(piper[0], buffMem , BUFFMAX - 1); 
		//close pipe
		close(piper[0]);
		//set last value to NULL
		buffMem[reader] = '\0'; 

		//output
		writeOuput(cmd[i], buffMem); 
		//free the cmd
		free(newcmd); 
		
	}

	free(buffMem);    
	free(cmd);

	return 0;
}

void writeOuput(char* command, char* output) {
     //Creates a file "Output.txt", and prints results
	FILE *fp;
	fp = fopen("output.txt","a");
  	fprintf(fp, "The output of: %s : is\n", command);
	fprintf(fp, ">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
    fclose(fp);
}


