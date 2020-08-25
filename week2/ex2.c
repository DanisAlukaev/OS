#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    char word[256];
    printf("Enter word to be inversed, please:\n");
    gets(word);
    int length=strlen(word);
    char reverse[length+1];
    int j=0;
    for(int i=length-1; i>=0; i--){
        reverse[j]=word[i];
        j++;
    }
    reverse[j] = '\0';
    printf("%s", reverse);
    return 0;
}
