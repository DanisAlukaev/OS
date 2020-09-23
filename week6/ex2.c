// BS19-02 Alukaev Danis
// Task 2.

#include <stdio.h>
#include <stdlib.h>

// Structure simulating process.
typedef struct processPair
{
    int AT;
    int BT;
    int CT;
    int WT;
    int TAT;
    int executed;
    int id;
} processPair_t;

/**
 * Sorts the input array of pairs <Arrival time(AT),Burst time(BT)> by Arrival time(AT) and Burst time(BT) using Bubble sort algorithm.
 * Time complexity: T(n)=O(n*n). Sorting is in-place.
 *
 * @param array - an array of pairs to be sorted.
 * @param n - number of elements in the input array.
 */
void processBubbleSort(processPair_t array[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(array[j].AT>array[j+1].AT)
            {
                processPair_t temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
            else if(array[j].AT==array[j+1].AT && array[j].BT>array[j+1].BT)
            {
                processPair_t temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}

/**
 * Decides what task should be performed next. Operates in array sorted firstly by AT, and secondly by BT.
 * Hence, it simulates "Shortest job next" logic.
 * Time complexity: T(n)=O(n).
 *
 * @param array - an array of processes.
 * @param n - number of elements in the input array.
 */
int getNextProcess(processPair_t array[], int n)
{
    for (int i=0; i<n; i++)
    {
        // If process is pending.
        if(array[i].executed==0)
        {
            // Mark as done.
            array[i].executed=1;
            // Return id.
            return i;
        }
    }
    // Otherwise, return id of the last process.
    return n;
}

int main()
{
    int numProcesses;
    scanf("%d", &numProcesses);
    // Array to store pairs <Arrival time(AT),Burst time(BT)> describing processes.
    processPair_t processes[numProcesses];
    // Variables to store Average Turnaround time, Average waiting time.
    float avTAT=0, avWT=0;
    // Get processes.
    for(int i=0; i<numProcesses; i++)
    {
        scanf("%d", &(processes[i].AT));
        scanf("%d", &(processes[i].BT));
        processes[i].executed=0;
    }
    // Sort all processes by Arrival time (AT).
    processBubbleSort(processes, numProcesses);
    // Compute Completion time (CT), Turn around time (TAT), Waiting time (WT) for all processes.
    // Assume that Completion time is the same with Exit time, i.e., the time when a process completes its execution and exit from the system.
    // TAT = CT - AT
    // WT = TAT - BT
    for(int i=0; i<numProcesses; i++)
    {
        // Get an id (index) of process to be performed.
        int j=getNextProcess(processes, numProcesses);
        if(j==0)
            processes[j].CT=processes[j].AT+processes[j].BT;
        else
            processes[j].CT=processes[j-1].CT+processes[i].BT;
        processes[j].TAT=processes[j].CT-processes[j].AT;
        processes[j].WT=processes[j].TAT-processes[j].BT;
    }
    // Print header of the table.
    printf("id\tAT\tBT\tCT\tTAT\tWT\n");
    // Print content of table: id of process (index in array), AT, BT, CT, TAT, WT.
    for(int i=0; i<numProcesses; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].WT);
        avTAT+=processes[i].TAT;
        avWT+=processes[i].WT;
    }
    // Compute and output Average Turnaround Time and Average Waiting Time.
    avTAT/=numProcesses;
    avWT/=numProcesses;
    printf("Average Turnaround Time = %f \n", avTAT);
    printf("Average Waiting Time = %f \n", avWT);
    return 0;
}
