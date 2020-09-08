#include <stdio.h>
#include <stdlib.h>

int main()
{
    // create array of chars to store command
    char command[50];
    while(1){
        // display readiness to execute new command
    	printf("> ");
        // read command
    	fgets(command,50,stdin);
        // the program will be terminated when the command will be <exit>
    	if(strcmp(command,"exit\n")==0)
    	    break;
        // execute a shell command <command>
    	system(command);
    }
    return 0;
}
