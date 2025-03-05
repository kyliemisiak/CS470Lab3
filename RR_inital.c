//CS 470 Lab 3

//headers
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
	//initialize variables
	int time = 0;
	int doneCount = 0;
	char execOrder[1000];
	int execIndex = 0;

	//initialize remaining times and waiting times
    	for (int i = 0; i < n; i++) {
		//remaining time
        	proc[i].remaining_time = proc[i].burst_time;
        	//waiting time
		proc[i].waiting_time = 0;
   	 }

    //round robin scheduling loop
    while (doneCount < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                //if process has remaining time
                int execution_time = (proc[i].remaining_time > quantum) ? quantum : proc[i].remaining_time;

                //add process to exec order
		//show format "P1 P2 P3.." like class example
                execOrder[execIndex++] = 'P';
		execOrder[execIndex++] = proc[i].process_id + '0';

                //update time and remaining time of process
                time += execution_time;
                proc[i].remaining_time -= execution_time;

                //if process is done, update the done count
                if (proc[i].remaining_time == 0) {
			proc[i].turnaround_time = time - proc[i].arrival_time;
			proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
			doneCount++;
                }
            }
        }
    }


    // Print the execution order
    printf("Execution Order: ");
    for (int i = 0; i < execIndex; i++) {
        if (i > 0) printf(" ");
        printf("%c%c", execOrder[i], execOrder[i+1]);
	i++;
    }
    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
   for (int i = 0; i < n; i++) {
        //turnaround time
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling


    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
