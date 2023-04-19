#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//sudoku file
int dokuGrid[9][9]; 
//when part of sodoku is valid it returns 1 to valid[], else it returns 0
int valid[11]; 
//tracks through valid array sections for the 3x3 subgrids
int subgrid = 2;


//structure to store the information to be passed to each thread
typedef struct {
    int row;
    int column;
} parameters;

//threads
pthread_t colThread, rowThread, thread_1, thread_2, thread_3, 
thread_4, thread_5, thread_6, thread_7, thread_8, thread_9;

//declare thread that checks columns, rows and 3x3 subgrids
void *checkCol(void *param);
void *checkRow(void *param);
void *checkSubgrid(void *param);

int main(int argc, char *argv[]) {

	//reading file from agrv[], portions the numbers to the sudoku board
	FILE *sudoku;
	sudoku = fopen(argv[1], "r");

	for (int n = 0; n < 9; n++) {

		for (int m = 0; m < 9; m++) {
			fscanf(sudoku, "%d %*[,]", &dokuGrid[n][m]);
		}
	}

	//assigs values to structure variable, creates multiple worker threads by passing INFO using structure variable
	parameters *rowsData = (parameters *) malloc(sizeof(parameters));
	rowsData->row = 0;
	rowsData->column = 0;

	parameters *colData = (parameters *) malloc(sizeof(parameters));
	colData->row = 0;
	colData->column = 0;

	parameters *subgrid_1 = (parameters *) malloc(sizeof(parameters));
	subgrid_1->row = 0;
	subgrid_1->column = 0;

	parameters *subgrid_2 = (parameters *) malloc(sizeof(parameters));
	subgrid_2->row = 0;
	subgrid_2->column = 3;

	parameters *subgrid_3 = (parameters *) malloc(sizeof(parameters));
	subgrid_3->row = 0;
	subgrid_3->column = 6;

	parameters *subgrid_4 = (parameters *) malloc(sizeof(parameters));
	subgrid_4->row = 3;
	subgrid_4->column = 0;

	parameters *subgrid_5 = (parameters *) malloc(sizeof(parameters));
	subgrid_5->row = 3;
	subgrid_5->column = 3;

	parameters *subgrid_6 = (parameters *) malloc(sizeof(parameters));
	subgrid_6->row = 3;
	subgrid_6->column = 6;

	parameters *subgrid_7 = (parameters *) malloc(sizeof(parameters));
	subgrid_7->row = 6;
	subgrid_7->column = 0;

	parameters *subgrid_8 = (parameters *) malloc(sizeof(parameters));
	subgrid_8->row = 6;
	subgrid_8->column = 3;

	parameters *subgrid_9 = (parameters *) malloc(sizeof(parameters));
	subgrid_9->row = 6;
	subgrid_9->column = 6;

	//return values used for pthread join
	void * rows;
	void * cols; 
	void * first_sq;
	void * second_sq;
	void * third_sq; 
	void * fourth_sq; 
	void * fifth_sq;
	void * sixth_sq;
	void * seventh_sq; 
	void * eighth_sq;  
	void * ninth_sq;

	//create pthreads
	pthread_create(&colThread, NULL, checkCol, (void *) colData);
	pthread_create(&rowThread, NULL, checkRow, (void *) rowsData);
	pthread_create(&thread_1, NULL, checkSubgrid, (void *) subgrid_1);
	pthread_create(&thread_2, NULL, checkSubgrid, (void *) subgrid_2);
	pthread_create(&thread_3, NULL, checkSubgrid, (void *) subgrid_3);
	pthread_create(&thread_4, NULL, checkSubgrid, (void *) subgrid_4);
	pthread_create(&thread_5, NULL, checkSubgrid, (void *) subgrid_5);
	pthread_create(&thread_6, NULL, checkSubgrid, (void *) subgrid_6);
	pthread_create(&thread_7, NULL, checkSubgrid, (void *) subgrid_7);
	pthread_create(&thread_8, NULL, checkSubgrid, (void *) subgrid_8);
	pthread_create(&thread_9, NULL, checkSubgrid, (void *) subgrid_9);

	//pthread_join() equivalent to wait(), for each child thread parent will wait
	pthread_join(colThread, &cols);
	pthread_join(rowThread, &rows);
	pthread_join(thread_1, &first_sq);
	pthread_join(thread_2, &second_sq);
	pthread_join(thread_3, &third_sq);
	pthread_join(thread_4, &fourth_sq);
	pthread_join(thread_5, &fifth_sq);
	pthread_join(thread_6, &sixth_sq);
	pthread_join(thread_7, &seventh_sq);
	pthread_join(thread_8, &eighth_sq);
	pthread_join(thread_9, &ninth_sq);

	/* after all children returns, you can check the status array that is visible to everyone and see if it is valid. 
	You then print out the sudoku and result*/
	int k = 0;
	while (k < 11) {

 		/*
		if the thread is valid, valid[k] == 1
 		else thread is not valid, and sodoku puzzle is not valid
		*/
		if (valid[k] == 1) { 
			k++;
		} else {
			printf("The Sudoku Puzzle is invalid. \n");
			exit(0);
		}

	}

	printf("Sudoku Puzzle Solution is: ");

	for (int n = 0; n < 9; n++) {
		printf("\n");
		
		for (int m = 0; m < 9; m++) {
			printf("%d ", dokuGrid[n][m]);
		}
	}

	printf("\n");
	printf("The Sudoku Puzzle is valid \n");

	return 0;
}

//check all columns 
void *checkCol(void *params) {

	int n, m;
	parameters * colCheck = (parameters *) params;
	int beginCol = colCheck->column;
	int beginRow = colCheck->row;

	//sorting sudoku column, checks for duplicates, if true return 0
	for (n = beginCol; n < 9; n++) {

		//array to hold sorted column
		int col[9]= {0}; 

		for (m = beginRow; m < 9; m++) {

			//value in the column
			int val = dokuGrid[n][m]; 

			//if col[val-1] == 0, value is not a duplicate then will be added to col array
			if (col[val-1] == 0 && val > 0) {
				col[val-1] = val;
			} else {
				//else value is a duplicate, and sodoku puzzle is invalid
				valid[0] = 0;
				pthread_exit(0);
			}
		}
	}
	valid[0] = 1;
	pthread_exit(0);
}

//check all rows
void *checkRow(void *params) {

	int n, m;
	parameters * r_work = (parameters *) params;
	int beginCol = r_work->column;
	int beginRow = r_work->row;

	//sorting sodoku row, checks for duplicates, if true return 0
	for (n = beginRow; n < 9; n++) {

		//array to hold sorted row
		int row[9]= {0};

		for (m = beginCol; m < 9; m++) {

			int val = dokuGrid[n][m];
				
			//if row[val-1] == 0, then value is not a duplicate, and will be added to row array
			if (row[val-1] == 0 && val > 0) {
				row[val-1] = val;
			} else {
				//else value is a duplicate, and sodoku puzzle is invalid
				valid[1] = 0;
				pthread_exit(0);
			}
		}
	}
	valid[1] = 1;
	pthread_exit(0);
}

//check all 3x3 subgrids
void *checkSubgrid(void *params) {

	int n, m;
	parameters * worker = (parameters *) params;
	int beginRow = worker->row;
	int beginCol = worker->column;

	//array to hold sorted 3x3 grid
	int grid[9] = {0};

	//sorts sudoku subgrids and checks for duplicates, if duplicates are found, return 0
	for (n = beginRow; n < beginRow + 3; ++n) {
		for (m = beginCol; m < beginCol + 3; ++m) {

			int val = dokuGrid[n][m];

			//if sqaure[val-1] == 0, then value is not a duplicate and will be added to grid array
			if (grid[val-1] == 0 && val > 0) {
				grid[val-1] = val;
			} else {
				//else its a duplicate, sodoku puzzle is invalid
				valid[subgrid] = 0;
				subgrid++;
				pthread_exit(0);
			}
		}
	}		
	valid[subgrid] = 1;
	subgrid++;
	pthread_exit(0);
}

