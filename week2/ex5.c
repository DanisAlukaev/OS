#include <stdio.h>
#include <limits.h>
#include <float.h>

void RStriangle(int n){
    // function that print right-side-up triangle of height n
    for(int i=0; i<n; i++){
        for(int j=0; j<i+1; j++)
            printf("*");
        printf("\n");
    }
}

void Rtriangle(int n){
    // function that print isosceles triangle of height n
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++)
            printf(" ");
        for(int j=0; j<i*2+1; j++)
            printf("*");
        printf("\n");
    }
}

void square(int n){
    // function that print square of height n
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            printf("*");
        printf("\n");
    }
}

void halfDiamond(int n){
    // function that print right half of diamond of height 2n-1
    for(int i=0; i<n; i++){
        for(int j=0; j<i+1; j++)
            printf("*");
        printf("\n");
    }
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<i; j++)
            printf("*");
        printf("\n");
    }
}


int main()
{
    int n;
    printf("Enter height of the figure, please:\n");
    scanf("%d", &n);
    // RStriangle(n);
    // Rtriangle(n);
    // square(n);
    halfDiamond(n);
    return 0;
}
