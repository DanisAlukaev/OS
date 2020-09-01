// BS19-02 Alukaev Danis
// Task 2.

#include <stdio.h>
#define N 10

/**
 * Sorts the input array of integer numbers using Bubble sort algorithm.
 * Time complexity: T(n)=O(n*n). Sorting is in-place.
 *
 * @param array - an array of numbers to be sorted.
 * @param n - number of elements in the input array.
 */
void intBubbleSort(int array[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(array[j]>array[j+1]){
                int temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}

int main(){
    int test[N];
    // create an array of N numbers arranged from N to 0 (i.e. reversed)
    for(int i=0; i<N; i++)
        test[i]=N-i;
    // call bubble sort function
    intBubbleSort(test,N);
    // print the array after sorting
    for(int i=0; i<N; i++)
        printf("%d ", test[i]);
}
