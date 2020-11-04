// BS19-02 Alukaev Danis
// Task 2.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LENGTH 20

int main(int argc, char *argv[])
{
    // Flag signalizing that user specified "-a" command line option.
    int APPEND=0;
    // Determine number of files specified by user.
    int n_files=0;
    if(strcmp(argv[1], "-a") == 0)
    {
        // Number of files is number of parameters passed to main without its name and -a option.
        n_files=argc-2;
        // Set flag to 1.
        APPEND=1;
    }
    else
        // Number of files is number of parameters passed to main without its name.
        n_files=argc-1;
    // Create array of integers to store descriptors of specified in command files.
    int descriptors[n_files];
    // Open files.
    if(APPEND)
        for(int i=0; i<n_files; i++)
            // Create file if it does not exist and open it in O_RDWR and O_APPEND mode.
            descriptors[i]=open(argv[i+2], O_CREAT | O_RDWR | O_APPEND, 0777);
    else
        for(int i=0; i<n_files; i++)
            // Create file if it does not exist and open it in O_RDWR mode.
            descriptors[i]=open(argv[i+1], O_CREAT | O_RDWR, 0777);
    // Create auxiliary variable to read file.
    char new_char;
    // Read STDIN.
    while(read(STDIN_FILENO, &new_char, 1)>0)
        for(int i=0; i<n_files; i++)
            // Iteratively write to file characters from STDIN.
            write(descriptors[i], &new_char, 1);
    // Close files.
    for(int i=0; i<n_files; i++)
        close(descriptors[i]);
    return 0;
}
