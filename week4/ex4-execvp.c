#include <stdio.h>
#include <stdlib.h>

int main(){
    // create array of chars to store command
    char command[500];
    while(1){
        // create array of words to store command and arguments separately
        char* argv[500];
        // read command
        fgets(command,500,stdin);
        if(strcmp(command,"exit\n")==0)
            // the command <exit> terminate program
            break;
        // allocate memory for command w/o arguments
        argv[0]=(char*)malloc(500);

        // parse command
        // i - to iterate through symbols in command
        // j - current argument in command
        // k - to iterate through symbols in argument
        int i=0,j=0,k=0;
        while(1){
            if(command[i]==' '){
                // allocate memory to new argument
                i++;
                j++;
                k=0;
                argv[j]=(char*)malloc(500);
            }
            else if(command[i]!='\n'){
                // move symbol from command line to respective word in argv
                argv[j][k]=command[i];
                i++;
                k++;
            }
            else{
                // execvp expects the last element in argv to be a NULL
                j++;
                for(int it=j;it<500;it++)
                    argv[it]=NULL;
                break;
            }
        }

        // duplicate (fork) process
        int PID=fork();
        if(PID==0)
            // execute from duplicated (child) process
            execvp(argv[0],argv);
    }
  return 0;
}
