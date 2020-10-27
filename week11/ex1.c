// BS19-02 Alukaev Danis
// Task 1.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

char* filepath = "ex1.txt";
char* my_string = "This is a nice day";

int main()
{
    // Open the file in O_RDWR mode.
    // System call open returns the file descriptor.
    int descriptor = open(filepath, O_RDWR);
    // Determine the string length.
    int string_len = strlen(my_string);
    // System call fstat utilizes structures stat.
    // Create an instance of this structure.
    struct stat info;
    // Retrieve information about the file using its descriptor.
    fstat(descriptor, &info);
    // Determine the size of file, in bytes.
    int file_size = info.st_size;
    // Create new mapping in the virtual address space.
    char* area = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
    // Truncate the file to string length.
    ftruncate(descriptor, string_len);
    // Copy new string to the mapped area.
    strncpy(area, my_string, string_len);
    // Delete the mapping.
    munmap(my_string, string_len);
    close(descriptor);
    return 0;
}
