#include <stdio.h>
#include <limits.h>
#include <float.h>

void swap(int *first_ptr, int *second_ptr){ 
   // function that swaps two integers
   int temp = *first_ptr;
   *first_ptr = *second_ptr;
   *second_ptr = temp;
}

int main()
{
    int first, second;
    printf("Enter first integer, please:\n");
    scanf("%d", &first);
    printf("Enter second integer, please:\n");
    scanf("%d", &second);
    swap(&first, &second);
    printf("first: %d, second: %d\n", first, second);
    return 0;
}
