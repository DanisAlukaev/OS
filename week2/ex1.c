#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    // declare three variables of int, float and double type
    // assign to them maximum values (for int such a value located in <limits.h>,
    // for float and double in <float.h>)
    int var_int=INT_MAX;
    float var_float=FLT_MAX;
    double var_double=DBL_MAX;
    // print the size of variables in bytes
    printf("int size: %lu\n", sizeof(var_int));
    printf("float size: %lu\n", sizeof(var_float));
    printf("double size: %lu\n", sizeof(var_double));
    return 0;
}
