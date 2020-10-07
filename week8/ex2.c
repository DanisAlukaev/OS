// BS19-02 Alukaev Danis
// Task 2.

/*
For this task was used the following shell script:

#!/bin/bash
gcc ex2.c -o ex2
./ex2 & vmstat 1

The following table was obtained after 10 seconds:

procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 2  0    268  85988  70916 962604    1    3 16849  2529 1006 8346 76 21  2  1  0
 1  0   1036 118052  70924 941144    0  656  3196   800  801 3449 81 18  0  1  0
 2  0   1036  80580  73040 958612    0    0 17876    92 2631 6057 58  5  0 38  0
 1  0   1036  77492  73120 958968    0    0   341     0  484 2756 45  5 50  1  0
 2  0   1036  68224  74812 961352    0    0  2783     0  673 6005 33 18 45  3  0
 2  0   1292  84228  75448 925836    0  312   823   312  585 9304 70 29  0  1  0
 0  0   1292  70320  76088 928800    0    0  1712     0  400 1827 40  6 54  0  0
 0  0   1292  79528  76092 909728    0  100     0 84524  259  377  6  4 83  7  0
 0  0   1804  89408  76104 877940    0  360     4   484  195  690  9  6 85  0  0
 0  0   1804  79076  76104 877940   16    0    16     0  117  307  5  2 92  1  0

Both "si" (amount of memory swapped in from disk per second) and "so" (amount of memory swapped to disk per second) 
have non-zero values when the swapping happened. As one can see, mostly swaps out (swaps to disk) occur to provide 
space in the RAM for the current process. As the program finished, some data are loaded from the disk, i.e., "si" = 16 
for the last entry in the above table.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10

int main()
{
    for(int i=0; i<N; i++)
    {
        // Allocate 10 MB of memory.
        int* block=(int*)malloc(10485760);
        // Fill it with zeros.
        memset(block,0,10485760);
        sleep(1);
    }
    return 0;
}