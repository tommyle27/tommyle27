#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_IN 200

// int variables
int *avail; //for available amount of each resource
int **allo; //for amount allocated to each customer
int **needs; //for remaining need of each customer

// the even sem
sem_t sem_even;
//the odd sem
sem_t sem_odd;

// void Calculating function
void needCalc(int i, int j, int **allo, int maximum[i][j], int **needs);
//re calc
void curr_recalc();
//int banker algo
int bankerAlgorithm(int m, int n, int **allo, int maximum[n][m], int avail[m], int **needs, int arr[n]);
void *threadRun(void *p);

//struct cstmer
typedef struct cstmer {
	int cstmers;
	int rcordSize;
} Customer;

Customer *cstom;

// the driver for the program
int main(int argc, char *argv[]) {

	// if statement for input error
	if(argc<2) {
		printf("Input error\n");
		// exit
		exit(1);
	}

	// Intializing Semaphores
	sem_init(&sem_even, 0, 0);
	sem_init(&sem_odd, 0 ,0);

	// int var to calc the avail size
	int sizeAvail = argc - 1;

	//openning File to get cstmers amount
	FILE *in;

	// file lines count int
    int count_lines = 0;
    char c;

    // opening the file in r mode
    in = fopen("sample_in_banker.txt", "r");

	// if statemt to check if the file is opened
	if(!in)	{
		// PRINT statement
		printf("File Open Error: file not opened\n");
		// exit
		exit(1);
	}

    // take the char from the file and store it in a var
    c = getc(in);

    // while loop as long as c doees not = EOF
	while (c != EOF) {
        // if loop finds \n, add to counter
        if (c == '\n')
            count_lines++;
        c = getc(in);
    }

	fclose(in);

	// findint the number of people based on input
	int cstmers = count_lines;

	// print the number of clients
	printf("Number of Customers: %d\n", cstmers);

	//arrays
	cstom = (Customer*)malloc(sizeof(Customer));
	// cstom to record size into Availablee size
	cstom->rcordSize = sizeAvail;
	// cstom to cstomers update cstmers
	cstom->cstmers = cstmers;

    // allocating array dynamically to available size
	avail = (int*)malloc(sizeAvail * sizeof(int));

	// if statement when avail = null and that causes an error
	if (avail == NULL) {
        // PRINT statement
        printf("Malloc Error\n");
        // exit
        exit(1);
    }

	// avail array to argv values
	// FOR LOOP
	for (int i = 0; i < sizeAvail; i++) {
		avail[i] = atoi(argv[i + 1]);
	}

	// allocate dynamiclly array for ALLO
	allo = (int **)malloc(cstmers * sizeof(int *));

	// if statement when allo = null and that causes an error
	if (allo == NULL) {
        // PRINT statement
        printf("Malloc Error\n");
        // exit
        exit(1);
    }

	// FOR LOOP
	for (int i = 0; i < cstmers; i++) {
		allo[i] = (int *)malloc(sizeAvail * sizeof(int));
	}

	// For loop to initializing allo array to 0
	for(int m = 0; m < cstmers; m++) {
	    // loop inside a loop for allo
    	for(int n = 0; n < sizeAvail; n++)
    		allo[m][n] = 0;
	}


	// array for needs
	needs = (int **)malloc(cstmers * sizeof(int *));

	// if statement when needs = null and that causes an error
	if (needs == NULL) {
        // PRINT statement
        printf("Malloc Error\n");
        // exit
        exit(1);
    }

	for (int i = 0; i < cstmers; i++) {
		needs[i] = (int *)malloc(sizeAvail * sizeof(int));
	}

	

	// reading values from file and inserting them in an array
	// creating an array
	int maximum[cstmers][sizeAvail];

	// making maximum array to zeros
	// for loop
	for(int m = 0; m < cstmers; m++) {
	    // for loop inside a for loop
    	for(int n = 0; n < sizeAvail; n++) {
    		maximum[m][n] = 0;
    	}
	}

	// opening the sample file to read for values
	in = fopen("sample_in_banker.txt", "r");

    //struct
	struct stat st;

	// return value of fstat
	if (fstat(fileno(in), &st) != 0) {
		printf("Error: failed to get file status.\n");
		fclose(in);
		exit(EXIT_FAILURE);
	} 

	char* file_vals = (char*)malloc(((int) st.st_size + 1)* sizeof(char));
	file_vals[0]='\0';

	// adding vals from the file into file_vals string
	while(!feof(in)) {
		char ln[100];
		if(fgets(ln, 100, in) != NULL)
			strncat(file_vals, ln, strlen(ln));
	}

    //close
	fclose(in);
	char* lines[cstmers];
	char *comm = NULL;
	int i = 0; // initiallizing int i
	comm = strtok(file_vals,"\r\n");

	// while comm is not null loop adding data from file_vals str to the linesarray
	while(comm != NULL)	{
		lines[i] = malloc(sizeof(comm)*sizeof(char));
		strcpy(lines[i],comm);
		//incramenting
		i++;
		comm = strtok(NULL,"\r\n");
	}

	// Tokenize each ln and add individual numbers into the array
	for(int k = 0; k < cstmers; k++) {

		char* token = NULL;
		int l = 0;
		token =  strtok(lines[k],",");

		while(token != NULL) {
			maximum[k][l] = atoi(token);
			//incramenting
			l++;
			token = strtok(NULL,",");
		}
	}

    // PRINT statement to display the currently Avail resources
	printf("Currently Available resources:");

    // for loop to show avail resources
	for (int i = 0; i < sizeAvail; i++) {
	    // PRINT statement
		printf(" %d", avail[i]);
	}

    // PRINT statement for extra line
	printf("\n");

	//printing the Max_resources from file
	printf("Maximum resources from file:\n");
	// for loop for when cstmers is more thn i
	for (int i = 0; i < cstmers; i++) {
	    // nested for loop to show max resources
    	for (int j = 0; j < sizeAvail; j++) {
    	    // PRINT statement
			printf("%d ", maximum[i][j]);
    	}
        // PRINT statement
		printf("\n");
	}

	// initializing the char arrays
	char init[MAX_IN];
    char check[MAX_IN];

    //char array for resource request
    char req[MAX_IN] = "RQ";

    //char array for releasing
    char rel[MAX_IN] = "RL";
    char str[MAX_IN] = "*\n";

    // safe mode sequence
    char run[MAX_IN] = "run\n";

    // close the program
    char exit_prog[MAX_IN] = "exit\n";

	//requesting initial request for running while loop
	// PRINT statement to ask user for checkm
	printf("Enter Command: ");
	fgets(init, MAX_IN, stdin);

	//copy
	strcpy(check, init);

	// int work variable set to 0 for now
	int work = 0;

	// when exit hasnt been called
	while (strcmp(check,exit_prog) != 0) {

	    // if statement for when work is more than 0
		 if (work > 0) {
		    // PRINT statement  to ask user for checkm
			printf("Enter Command: ");
            fgets(init, sizeof init, stdin);
            //copy
            strcpy(check, init);
        }

		// a new int var for the str
		int string_T = 0;

		// splitting the str using a for loop
		for (int z = 0; check[z] != '\0'; z++) {
		    // if check[z] = any of the following: " ", \t, or \n
			if (check[z] == ' ' || check[z] == '\t' || check [z] == '\n') {
				string_T++;
			}
		}

		char *tkn = strtok(check, " ");
		char *input_str[MAX_IN];
		// int i setting to 0
		int i = 0;

		// if the total string is more or = to 2
		if (string_T >= 2) {
		    // while loop inside the if statement as long as tkn does not = to null and if i is less than or = cstmers
			while (tkn != NULL && i <= cstmers)	{
				input_str[i] = tkn;
				tkn = strtok(NULL, " ");
				i += 1;
			}
	
		// else if string_t is less than 2
		} else {
			strcpy(input_str[0], check);
		}

		// updating the length to i
		int lengthOfString = i;
		// reset i
		i = 0;

	    //The resource request if statement
		if (strcmp(input_str[0], req) == 0)	{
			if (atoi(input_str[1]) >= cstmers)	{
			// PRINT statement
				printf("Allocated index cannot be larger then Max Number of Customers\n");
				// continue;
			} else {
			    // adding data
				for (int y = 2; y < (lengthOfString); y++) {
				    // allo resource information from str to int
					allo[atoi(input_str[1])][y-2] = atoi(input_str[y]);
				}
				// PRINT statement
				printf("State is safe, and request is satisfied\n");
			}

		// the resource release checkm else if statement
		} else if (strcmp(input_str[0], rel) ==0) {
            // A int var used when the requested release checkm is not satisfied
            int flag_quit;

            // if statement
			if (atoi (input_str[1]) >= cstmers) {
			// PRINT statement
				printf("Error: Allocated index exeeds Maximum Customer Number\n");
				// continue;
			} else {
				for (int q = 2; q < (lengthOfString); q++)	{
					int valRelease; // int var for release val

					//calc release value from the array
					valRelease = allo[atoi(input_str[1])][q - 2] - atoi(input_str[q]);

                    // if the val is less than 0
					if (valRelease < 0)	{
					// PRINT statement
						printf("Release is not satisfied\n");
						flag_quit = 1;
						break;

					// if val > 0
					} else {
					    // converting val of current pointed release value
						allo[atoi(input_str[1])][q - 2] = valRelease;
					}

					if (q == lengthOfString - 1) {
					    // PRINT statement
						printf("The resources have been released successfully\n");
					}
				}

				if (flag_quit == 1) {
					continue;
				}
			}

		//display the details comand
        } else if (strcmp(input_str[0], str) == 0) {
			// print statment to show available resources
			printf("Available Resources: ");
			// calling the func
			curr_recalc();

			for (int l = 0; l < sizeAvail; l++) {
			// PRINT statement
				printf("%d ", avail[l]);
			}

            // PRINT statement
			printf("\n\n");

			// Printing the max resources
			printf("Maximum Resources: \n");

			for (int l = 0; l < cstmers; l++) {
				for (int p = 0; p < sizeAvail; p++) {
				    // PRINT statement
					printf("%d ", maximum[l][p]);
				}
                // PRINT statement
				printf("\n");
			}

            // PRINT statement
			printf("\n");
			//printing the allo resources
			printf("Allocated Resources: \n");

			// for loop to print the resources
			for (int l = 0; l < cstmers; l++) {
				for (int p = 0; p < sizeAvail; p++) {
				    // PRINT statement
					printf("%d ", allo[l][p]);
				}
				// PRINT statement
				printf("\n");
        	}

            // PRINT statement  to add ln
			printf("\n");
			// Prining the needs resources
			printf("Need Resources: \n");

			// calling the func
			needCalc(sizeAvail, cstmers, allo, maximum, needs);

			for (int l = 0; l < cstmers; l++) {
				for (int p = 0; p < sizeAvail; p++) {
				    // PRINT statement
					printf("%d ", needs[l][p]);
				}
                // PRINT statement
				printf("\n");
			}
            // PRINT statement
			printf("\n");

	    // running threads and finding safe seq
		} else if (strcmp(input_str[0], run) == 0) {

			// Temporary array for storing data
			int arr[cstmers]; 
			//calling the func
			needCalc(sizeAvail, cstmers, allo, maximum, needs);
			int respond = bankerAlgorithm(sizeAvail, cstmers, allo, maximum, avail, needs, arr);

			// if respond does not = 0
			if (respond != 0) {
			    // PRINT statement
				printf("The safe sequence is not found:(\n");
				// exit
				exit(1);
			}

			for (int g = 0; g < cstmers; g++) {
				int ind = arr[g];
				// PRINT statement
				printf("--> Customer/Thread %d\n", ind);
				pthread_t tid;
				pthread_create(&tid, NULL, threadRun, &ind);
				pthread_join(tid, NULL);
			}
		}

		work += 1;
	}

	// freeing data
	free(allo);
	free(needs);
	free(avail);
	free(file_vals);
	// return statement
	return 0;
}

int j, m;
// calc for needed resources
void needCalc(int i, int n, int **allo, int maximum[j][i], int **needs) {

	for (int m = 0; m < j; m++)	{
		for (int n = 0; n < i; n++) {
			needs[m][n] = maximum[m][n] - allo[m][n];
		}
	}
}

// calc for curr resources
void curr_recalc() {
    // int temporary vars, temp and temp2
	int temp;
	int temp2;

	for (int m = 0; m < cstom->rcordSize; m++)	{
		temp = 0;
		for (int n = 0; n < cstom->cstmers; n++) {
			temp = temp + allo[n][m];
		}
		temp2 = avail[m] - temp;
		avail[m] = temp2;
	}
}

// the bankers algo
int bankerAlgorithm(int k, int n, int **allo, int (*maximum)[m], int avail[k], int **needs, int arr[n]) {
    // 3 temp vars ijh
    int h, i, j;
    int safe = 1;

    int f[n], ind = 0;
    for (h = 0; h < n; h++) {
        f[h] = 0;
    }

    int y = 0;
    for (h = 0; h < k; h++) {
        for (i = 0; i < n; i++) {

            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < k; j++) {
                    if (needs[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)  {
                    arr[ind++] = i;
                    for (y = 0; y < k; y++) {
                        avail[y] += allo[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (f[i] == 0){
            safe = 0;
        }
    }

    if (safe == 0){
    // return statement
        return -1;
    }

    printf("Safe Sequence is: <");

    for (i = 0; i < n - 1; i++){
        printf("%d ", arr[i]);
    }

    printf("%d>\n", arr[n - 1]);
	printf("\n\n\n");

    // return statement
    return 0;
}

//threadRun - This function is run by a thread and basically displays all info
void *threadRun(void *p) {

	int *thred = (int *)p;

	printf("\tAllocated resources:\t");

	for (int i = 0; i < cstom->rcordSize; i++){
		printf("%d ", allo[*thred][i]);
	}
	//add line
	printf("\n");

	// print statemnt for needed title
	printf("\tNeeded:\t");

    for (int i=0; i< cstom->rcordSize; i++) {
        printf("%d ", needs[*thred][i]);
    }

    // add line and print available title
    printf("\n");

	printf("\tAvailable:\t");

    for (int i=0; i< cstom->rcordSize; i++){
        printf("%d ", avail[i]);
    }

    // add line
    printf("\n");

    printf("\tThread has started\n");
    printf("\tThread has finished\n");
    printf("\tThread is releasing resources\n");

	printf("\tNew Available:\t");

	for (int i=0; i< cstom->rcordSize; i++) {
        avail[i] =  avail[i] + allo[*thred][i];
        printf("%d ", avail[i]);
    }
    // add line
    printf("\n");
	// return statement
	return NULL;
}
