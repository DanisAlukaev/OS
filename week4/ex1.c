// BS19-02 Alukaev Danis
// Task 1.

#include <stdio.h>
#include <stdlib.h>

/*
The following program prints:
Hello from parent [7201 - 1] 
Hello from child [7202 - 1] 
Hello from parent [7203 - 2] 
Hello from child [7204 - 2] 
Hello from parent [7205 - 3] 
Hello from child [7206 - 3] 
Hello from parent [7207 - 4] 
Hello from child [7208 - 4] 
Hello from parent [7209 - 5] 
Hello from child [7210 - 5] 
Hello from parent [7211 - 6] 
Hello from child [7212 - 6] 
Hello from parent [7213 - 7] 
Hello from child [7214 - 7] 
Hello from parent [7215 - 8] 
Hello from child [7216 - 8] 
Hello from parent [7217 - 9] 
Hello from child [7218 - 9] 
Hello from parent [7219 - 10]

Since for the virtual machine is allocated only one core of my processor, the processes executed right in order. 
As a result, the processes of the child and the parent alternate.
*/

int main(int args, char *argv[])
{
    // variable for received identificator of created process	
    int n;
    // receive identificator from outer for-loop (see ex1.sh)
    sscanf(argv[1],"%d",&n);
    // create new process by duplicating the calling process
    // PID equals 0 for child, otherwise for parent
    int PID=fork();
    if(PID>0)
        // initial (parent) process
        printf("Hello from parent [%d - %d] \n",getpid(),n);
    else if(PID==0)
        // duplicated (child) process
        printf("Hello from child [%d - %d] \n",getpid(),n);
    else
        // error
        return -1;
    return 0;
}
