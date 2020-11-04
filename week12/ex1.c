// BS19-02 Alukaev Danis
// Task 1.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LENGTH 20

char* source = "/dev/random";
char* target = "ex1.txt";

int main()
{
    // Open the source file in O_RDONLY mode.
    // Create target file if it does not exist and open it in O_RDWR mode.
    // System call open returns the file descriptor, save it for both files.
    int d_source = open(source, O_RDONLY);
    int d_target = open(target, O_CREAT | O_RDWR, 0777);
    // Create char array to store random string read from source file.
    char random_string[LENGTH];
    // Read random string from source file, put it in char array.
    read(d_source, random_string, LENGTH);
    // Write random string to target file.
    write(d_target, random_string, LENGTH);
    // Close both files.
    close(d_source);
    close(d_target);
    return 0;
}
