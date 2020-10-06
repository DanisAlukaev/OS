// BS19-02 Alukaev Danis
// Task 4.

/*
Program output:
Maximum resident set size: 11356 KB 
Maximum resident set size: 21688 KB 
Maximum resident set size: 31984 KB 
Maximum resident set size: 42280 KB 
Maximum resident set size: 52576 KB 
Maximum resident set size: 62872 KB 
Maximum resident set size: 72904 KB 
Maximum resident set size: 83200 KB 
Maximum resident set size: 93496 KB 
Maximum resident set size: 103792 KB
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#define N 10

int main()
{
    // Structure to store resource usages.
    struct rusage usage;
    for(int i=0; i<N; i++)
    {
        // Allocate 10 MB of memory.
        int* block=(int*)malloc(10485760);
        // Fill it with zeros.
        memset(block,0,10485760);
        // Get the resource usage statistics for current process.
        getrusage(RUSAGE_SELF, &usage);
        // Print the maximum resident set size used (in kilobytes).
        printf("Maximum resident set size: %ld KB \n",usage.ru_maxrss);
        sleep(1);
    }
    return 0;
}
