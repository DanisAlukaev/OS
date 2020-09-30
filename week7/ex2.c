// BS19-02 Alukaev Danis
// Task 2.

/*
Sample output:
Type no. if integers in array:
7
0 1 2 3 4 5 6
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Number of elements in array.
    int N;
    // Prompt the user to enter N.
    printf("Type no. if integers in array: \n");
    // Read N.
    scanf("%d", &N);
    // Allocating the memory.
    int *arrayN = malloc(N*sizeof(int));
    // Fills the array with incremental values starting from 0.
    for(int i=0; i<N; i++)
        *(arrayN+i)=i;
    // Output the array.
    for(int i=0; i<N; i++)
        printf("%d ", *(arrayN+i));
    free(arrayN);
    return 0;
}
