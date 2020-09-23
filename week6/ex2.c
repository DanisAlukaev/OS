// BS19-02 Alukaev Danis
// Task 2.
/**
 * Assumption: Completion time is the same with Exit time, i.e., the time when a process completes its execution and exit from the system.
*/

/*
Sample input:
14
0 1
0 1
0 1
3 1
3 2
3 3
7 3
7 2
7 1
13 1
13 2
13 3
17 1
17 2

Sample output:
id      AT      BT      CT      TAT     WT
0       0       1       1       1       0
1       0       1       2       2       1
2       0       1       3       3       2
3       3       1       4       1       0
4       3       2       6       3       1
5       3       3       9       6       3
8       7       1       10      3       2
7       7       2       12      5       3
6       7       3       15      8       5
9       13      1       16      3       2
10      13      2       18      5       3
12      17      1       19      2       1
13      17      2       21      4       2
11      13      3       24      11      8
Average Turnaround Time = 4.071429
Average Waiting Time = 2.357143
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
 * Schedules the input array of processes using "Shortest job next" logic.
 * Time complexity: T(n)=O(n*n).
 *
 * @param processes - an array of processes to be sorted.
 * @param numProcesses - number of processes in the input array.
 */
void processSJF(process_t processes[], int numProcesses)
{
    // Set initial time moment.
    int time = 0;
    for(int i = 0; i < numProcesses; i++)
    {
        // Find the least AT of pending processes.
        int leastAT=INT_MAX;
        for(int j=i; j<numProcesses; j++)
            if (processes[j].AT<leastAT)
                leastAT=processes[j].AT;
        // If no pending process at this moment.
        if(leastAT>time)
            time = leastAT;
        // Determine process with least BT that already "arrived" at this time moment.
        int leastBT=INT_MAX;
        int indexLeastBT=-1;
        for(int j=i; j<numProcesses; j++)
        {
            if(processes[j].AT<=time && processes[j].BT<leastBT)
            {
                indexLeastBT=j;
                leastBT=processes[j].BT;
            }
        }
        // Schedule pending process with least BT be next.
        process_t temp=processes[i];
        processes[i]=processes[indexLeastBT];
        processes[indexLeastBT]=temp;
        // Next process can be performed only after termination of current process.
        time=processes[i].BT+time;
    }
}

/**
 * Computes CT, TAT, WT. Operates on sorted array of processes.
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
    processSJF(processes, numProcesses);
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

