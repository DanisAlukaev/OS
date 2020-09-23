// BS19-02 Alukaev Danis
// Task 3.
// Assumption: Completion time is the same with Exit time, i.e., the time when a process completes its execution and exit from the system.

/*
Sample input:
10 3
0 1
0 2
0 4
0 6
0 8
11 8
11 6
11 4
11 2
11 1

Sample output:
id      AT      BT      CT      TAT     WT
0       0       1       1       1       0
1       0       2       3       3       1
2       0       4       25      25      21
3       0       6       28      28      22
4       0       8       40      40      32
5       11      8       42      31      23
6       11      6       37      26      20
7       11      4       38      27      23
8       11      2       23      12      10
9       11      1       24      13      12
Average Turnaround Time = 20.600000
Average Waiting Time = 16.400000
*/

/*
COMPARISON:
=================================================================|
Sample input from 4-th slide:
for ex1, ex2:
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

for ex3 (quantum=3):
14 3
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

Results:
1. First come, first served:
Average Turnaround Time = 4.571429
Average Waiting Time = 2.857143

2. Shortest job next:
Average Turnaround Time = 4.071429
Average Waiting Time = 2.357143

3. Round robin:
Average Turnaround Time = 4.571429
Average Waiting Time = 2.857143


Sample input from 6-th slide:
for ex1, ex2:
10
0 1
0 2
0 4
0 6
0 8
11 8
11 6
11 4
11 2
11 1

for ex3 (quantum=3):
10 3
0 1
0 2
0 4
0 6
0 8
11 8
11 6
11 4
11 2
11 1

Results:
1. First come, first served:
Average Turnaround Time = 17.600000
Average Waiting Time = 13.400000

2. Shortest job next:
Average Turnaround Time = 12.100000
Average Waiting Time = 7.900000

3. Round robin:
Average Turnaround Time = 20.600000
Average Waiting Time = 16.400000

In both sample cases presented in slides the least average turnaround time and waiting time are for the "Shortest job next"-policy
scheduler. However, it does not make any sense in general, and results may differ. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure simulating process.
// Consists of Arrival time(AT), Burst time(BT), Completion time (CT), Turn around time (TAT),
// Waiting time (WT), id (process sequence number from the input), time_left (shows how much time do we need to finish process),
// executed (flag).
typedef struct process
{
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int id;
    int time_left;
    int executed;
} process_t;

/**
 * Schedules the input array of processes using "Round Robin" logic.
 *
 * @param processes - an array of processes to be sorted.
 * @param numProcesses - number of processes in the input array.
 * @param quantum - allowance of CPU time.
 */
void processRR(process_t processes[], int numProcesses, int quantum)
{
    // Number of scheduled processes.
    int scheduled=0;
    // The current time moment
    int time = 0;
    // Repeat until all processes scheduled.
    while(numProcesses>scheduled)
    {
        // Find the least AT of pending processes.
        int leastAT=0;
        for(int i=0; i<numProcesses; i++)
            if(processes[i].time_left!=0 && leastAT>processes[i].AT)
                leastAT=processes[i].AT;
        // If no pending process at this moment.
        if(leastAT>time)
            time=leastAT;
        // Start scheduling.
        for(int i=0; i<numProcesses; i++)
        {
            if(processes[i].AT<=time && processes[i].time_left!=0)
            {
                // If CPU can finish current process in this time slot.
                if(processes[i].time_left<=quantum)
                {
                    time=processes[i].time_left+time;
                    // Process scheduled.
                    processes[i].time_left=0;
                    processes[i].CT=time;
                    scheduled++;
                    continue;
                }
                // Otherwise, decrease time left to finish process.
                processes[i].time_left-=quantum;
                time=quantum+time;
            }

        }
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
    // Compute TAT, WT for the first scheduled process (which arrival time is the least).
    for(int i=0; i<numProcesses; i++)
    {
        // Execute only pending processes.
        if(!processes[i].executed)
        {
            processes[i].TAT=processes[i].CT-processes[i].AT;
            processes[i].WT=processes[i].TAT-processes[i].BT;
            processes[i].executed=1;
        }
    }
}

int main()
{
    int numProcesses, quantum;
    // Variables to store Average Turnaround time (avTAT), Average waiting time(avWT).
    float avTAT=0, avWT=0;
    scanf("%d %d", &numProcesses, &quantum);
    // Array of processes.
    process_t processes[numProcesses];

    // Get processes.
    for(int i=0; i<numProcesses; i++)
    {
        scanf("%d", &(processes[i].AT));
        scanf("%d", &(processes[i].BT));
        processes[i].executed=0;
        processes[i].time_left=processes[i].BT;
        processes[i].id=i;
    }

    // Sort all processes by Arrival time (AT).
    processRR(processes, numProcesses, quantum);
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

