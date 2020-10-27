// BS19-02 Alukaev Danis
// Task 4.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

char* source = "ex1.txt";
char* target = "ex1.memcpy.txt";

int main()
{
    // Open the files in O_RDWR mode.
    // System call open returns the file descriptor.
    int d_source = open(source, O_RDWR);
    int d_target = open(target, O_RDWR);
    // System call fstat utilizes structures stat.
    // Create an instance of this structure.
    struct stat info;
    // Retrieve information about the source file using its descriptor.
    fstat(d_source, &info);
    // Determine the size of file, in bytes.
    int source_size = info.st_size;
    // Truncate the target file to size of source file.
    ftruncate(d_target, source_size);
    // Create new mappings in the virtual address space.
    char* a_source = mmap(NULL, source_size, PROT_READ, MAP_SHARED, d_source, 0);
    char* a_target = mmap(NULL, source_size, PROT_WRITE, MAP_SHARED, d_target, 0);
    // Copy new string to the mapped area.
    strncpy(a_target, a_source, source_size);
    // Delete the mapping.
    munmap(a_source, source_size);
    munmap(a_target, source_size);
    close(a_source);
    close(a_target);
    return 0;
}
