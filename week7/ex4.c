// BS19-02 Alukaev Danis
// Task 4.

/*
The output will be:
0 1 2 3 4
Reallocate equal-sized array with size 5.
0 1 2 3 4
Reallocate larger array with size 7.
0 1 2 3 4 0 0
Reallocate smaller array with size 3.
0 1 2
*/

// Define sizes for test:
// Original size.
#define O 5
// Equal-sized.
#define E 5
// Larger size.
#define L 7
// Smaller size.
#define S 3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/**
 * Tries to resize memory block pointed to by ptr.
 *
 * @param ptr - pointer to an array to be reallocated.
 * @param size - new size of the input array.
 */
void *myRealloc(void *ptr, size_t size)
{
    void *temp;
    size_t ptrSize=malloc_usable_size(ptr);
    if(ptr==NULL)
        // Allocate memory of size "size".
        temp=malloc(size);
    else
    {
        if(size==0)
            // Since required size is 0, deallocate the memory.
            free(temp);
        else
        {
            // Allocate memory.
            temp=malloc(size);
            // Copy content to new memory block.
            if(size>ptrSize)
                memcpy(temp,ptr,ptrSize);
            else
                memcpy(temp,ptr,size);
        }
    }
    // Deallocate the memory.
    free(ptr);
    return temp;
}

int main()
{
    // Create array of size O.
    int *testArray=malloc(O*sizeof(int));
    for(int i=0; i<O; i++)
        *(testArray+i)=i;
    for(int i=0; i<O; i++)
        printf("%d ", *(testArray+i));
    printf("\n");
    // Reallocate equal-sized array.
    printf("Reallocate equal-sized array with size %d.\n", E);
    testArray=myRealloc(testArray,E*sizeof(int));
    for(int i=0; i<E; i++)
        printf("%d ", *(testArray+i));
    printf("\n");
    // Reallocate larger array.
    printf("Reallocate larger array with size %d.\n", L);
    testArray=myRealloc(testArray,L*sizeof(int));
    for(int i=0; i<L; i++)
        printf("%d ", *(testArray+i));
    printf("\n");
    // Reallocate smaller array.
    printf("Reallocate smaller array with size %d.\n", S);
    testArray=myRealloc(testArray,S*sizeof(int));
    for(int i=0; i<S; i++)
        printf("%d ", *(testArray+i));
    printf("\n");
    free(testArray);
    return 0;
}
