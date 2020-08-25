#include <stdio.h>
#include <limits.h>
#include <float.h>

void triangle(int n){
    // function that print right-side-up triangle of height n
    // (the function for isosceles triangle see in ex5.c)
    for(int i=0; i<n; i++){
        for(int j=0; j<i+1; j++)
            printf("*");
        printf("\n");
    }
}

int main()
{
    int n;
    printf("Enter height of the triangle, please:\n");
    scanf("%d", &n);
    triangle(n);
    return 0;
}
