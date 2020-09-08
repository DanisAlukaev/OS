#include <stdio.h>
#include <stdlib.h>

int main(){
    char command[500];
    while(1){
        // display readiness to execute new command
        printf("> ");
        fgets(command,500,stdin);
        if(strcmp(command,"exit\n")==0)
            // the command <exit> terminate program
            break;
        // duplicate (fork) process
        int PID=fork();
        if(PID==0){
            // execute from duplicated (child) process
            system(command);
            break;
        }
    }
	return 0;
}
