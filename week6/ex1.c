// BS19-02 Alukaev Danis
// Task 1.
/**
 * Assumption: Completion time is the same with Exit time, i.e., the time when a process completes its execution and exit from the system.
*/

/*
Sample input:
6
1 1
3 3
4 2
5 3
2 1
0 4

id      AT      BT      CT      TAT     WT
5       0       4       4       4       0
0       1       1       5       4       3
4       2       1       6       4       3
1       3       3       9       6       3
2       4       2       11      7       5
3       5       3       14      9       6
Average Turnaround Time = 5.666667
Average Waiting Time = 3.333333
*/


#include <stdio.h>
#include <stdlib.h>

// Structure simulating process.
// Consists of Arrival time(AT), Burst time(BT), Completion time (CT), Turn around time (TAT),
// Waiting time (WT), id (process sequence number from the input), executed (flag).
typedef struct process
{
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int id;
    int executed;
} process_t;

/**
 * Sorts the input array of processes by AT using Bubble sort algorithm.
 * Time complexity: T(n)=O(n*n). Sorting is in-place.
 *
 * @param processes - an array of processes to be sorted.
 * @param numProcesses - number of processes in the input array.
 */
void processFCFS(process_t processes[], int numProcesses)
{
    for(int i=0; i<numProcesses-1; i++)
    {
        for(int j=0; j<numProcesses-i-1; j++)
        {
            if(processes[j].AT>processes[j+1].AT)
            {
                process_t temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
}

/**
 * Computes CT, TAT, WT. Operates on sorted array of processes.
 * Uses "First come, first served" logic.
 * Used formulas:
 * TAT = CT - AT
 * WT = TAT - BT
 *
 * @param array - an array of processes.
 * @param n - number of elements in the input array.
 */
void estimateProcesses(process_t processes[], int numProcesses)
{
    // Firstly, compute CT, TAT, WT for the first scheduled process (which arrival time is the least).
    processes[0].CT=processes[0].AT+processes[0].BT;
    processes[0].TAT=processes[0].CT-processes[0].AT;
    processes[0].WT=processes[0].TAT-processes[0].BT;
    processes[0].executed=1;
    // Then, compute same characteristics for the rest of processes.
    // Since CT of i-th process depends on CT of (i-1)-th process, we proceed with first process in advance.
    for(int i=1; i<numProcesses; i++)
    {
        // Execute only pending processes.
        if(!processes[i].executed)
        {
            processes[i].CT=processes[i-1].CT+processes[i].BT;
            processes[i].TAT=processes[i].CT-processes[i].AT;
            processes[i].WT=processes[i].TAT-processes[i].BT;
            processes[i].executed=1;
        }
    }
}

int main()
{
    int numProcesses;
    // Variables to store Average Turnaround time (avTAT), Average waiting time(avWT).
    float avTAT=0, avWT=0;
    scanf("%d", &numProcesses);
    // Array of processes.
    process_t processes[numProcesses];

    // Get processes.
    for(int i=0; i<numProcesses; i++)
    {
        scanf("%d", &(processes[i].AT));
        scanf("%d", &(processes[i].BT));
        processes[i].executed=0;
        processes[i].id=i;
    }

    // Sort all processes by Arrival time (AT).
    processFCFS(processes, numProcesses);
    // Compute CT, TAT, WT.
    estimateProcesses(processes, numProcesses);

    // Print the header of the table.
    printf("id\tAT\tBT\tCT\tTAT\tWT\n");
    // Print content of table: id, AT, BT, CT, TAT, WT.
    // Along the way count total TAT and WT.
    for(int i=0; i<numProcesses; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].WT);
        avTAT+=processes[i].TAT;
        avWT+=processes[i].WT;
    }
    // Compute and output average TAT and average WT.
    avTAT/=numProcesses;
    avWT/=numProcesses;
    printf("Average Turnaround Time = %f \n", avTAT);
    printf("Average Waiting Time = %f \n", avWT);
    return 0;
}
