// BS19-02 Alukaev Danis
// Task 5.

/*
The output will be:
s is Hello World
s[0] is Hello World
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // In order to prevent segmentation fault the following line can be changed:
    // char **s;
    // Allocate memory for **s:
    char **s = malloc(sizeof(char*));
    char foo[] = "Hello World";
    *s = foo;
    // The following line does not cause segmentation fault:
    // printf("s is %s\n",s);
    // it outputs not in accordance with the original idea though.

    // We can print the address using printf("s is %p\n",s);
    // The output will be:
    // s is 00DF1760
    // s[0] is Hello World

    // But for me it is better to make the argument of the char* type:
    printf("s is %s\n",*s);
    s[0] = foo;
    printf("s[0] is %s\n",s[0]);
    return(0);
}
