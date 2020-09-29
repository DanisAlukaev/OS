// BS19-02 Alukaev Danis
// Task 5.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // The segmentation fault is caused by the following line:
    // char **s;
    // This issue can be resolved by allocating memory for **s.
    char **s = malloc(sizeof(char*));
    char foo[] = "Hello World";
    *s = foo;
    // The following line does not cause segmentation fault:
    // printf("s is %s\n",s);
    // but outputs not in accordance with the original idea.
    // The argument should be of a type char*.
    printf("s is %s\n",*s);
    s[0] = foo;
    printf("s[0] is %s\n",s[0]);
    return(0);
}
