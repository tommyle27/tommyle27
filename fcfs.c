#include<stdio.h>

int main (int argc, char *argv[]) {

	// Reads the files elements into board array using for loop
    int x = 0;  
	int y = 0;
	int date[5][6];

    // reading file from agrv[] for thread ID, arrival time, and turnaround.
	FILE *curr;
	curr = fopen(argv[1], "r");

    // find values of id, arrive time, and burst time
	for (y = 0; y < 5; y++) {
		for (x = 0; x < 3; x++) {
			fscanf (curr, "%d %*[,]", &date[y][x]);
		}
	}

	int process[5];
    
	for (y = 0; y < 5; y++) {
		process[y] = date[y][0];
	}

	y = sizeof process / sizeof process[0];

	int time[5];

	for (x = 0; x < 5; x++) {
		time[x] = date[x][1];
	}

	int  burst_time[5];

	for (x = 0; x < 5; x++) {        
		burst_time[x] = date[x][2];
	}

    averageTime (process, y, time, burst_time);
    
    
    return 0;

}

// Driver code
// Function to find the temp waiting time
void findtempT (int process[], int n, int burstT[], int temporary[])
{
    // First processes waiting time is 0
    temporary[0] = 0;

    // This calculates the waiting time
    for (int  m = 1; m < n ; m++ )
        temporary[m] =  burstT[m - 1] + temporary[m - 1] ;

}

// This function is able to calculate the completion time
void findCompletionTime (int process[], int n, int burstT[], int temporary[], int comp[])
{
    // calculating completion time by adding the burstT[i] with temp[i]
    for (int  m = 0; m < n ; m++)
        comp[m] = burstT[m] + temporary[m];
}


void averageTime (int process[], int j, int at[], int burstT[])
{
    int temporary[j], i[j];
    int m = 0;

    // twmp time is found in this function
    findtempT (process, j, burstT, temporary);

    // completion time is found in this function
    findCompletionTime (process, j, burstT, temporary, i);

    // Displays all of the details
    printf("Thread ID  Burst time  Arrival Time  Completion Time   Turn around time   Waiting time \n");

    // Calculates and prints all the values
    for (int m = 0; m < j; m++)
    {
        printf("   %d ", (m + 1));
        printf("           %d ", at[m]);
        printf("            %d ", burstT[m]);
        printf("            %d", i[m]);
        printf("             %d", i[m] - at[m]);
        printf("                   %d\n", i[m] - at[m] - burstT[m]);

    }

    float pause;
    for (m = 0; m < 5; m++){
    	pause += i[m] - at[m] - burstT[m];
	}
    pause = pause/5;

    float avg_comp;
    for( m = 0; m < 5; m++){
		avg_comp += i[m] - at[m];
	}
    avg_comp = avg_comp/5;

    printf("Average waiting time = %.2f \n", pause);
    printf("\n");
    printf("Average turn around time = %.2f \n", avg_comp);

}