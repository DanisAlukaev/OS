// BS19-02 Alukaev Danis
// Task 1.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define MAX_LENGTH 15

char* filepath = "ex1.txt";
char* my_string = "This is a nice day";

/**
 * Opens a file with the specified path and writes a randomly generated string in it.
 *
 * @param filepath - path to the file.
 */
void generate_file(char* filepath)
{
    // Open the file.
    FILE *new_file = fopen(filepath, "w");
    // Generate seed.
    srand(time(0));
    // Define the length of the random string.
    int string_size = rand() % MAX_LENGTH + MAX_LENGTH / 4;
    // Allocate memory for the string.
    char* string = malloc(string_size * sizeof(char));
    // Define the set of letters that the word will consist of.
    int charset_size = 70;
    char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?! ";
    // Append random letters to string.
	for (int i = 0; i < string_size-1; i++)
        string[i] = charset[rand() % charset_size];
    // Denote the end of the string.
    string[string_size-1] = '\0';
    // Write the string in file.
	fprintf(new_file, string);
    // Close the file.
	fclose(new_file);
}

int main()
{
    // Generate the string and write it in file.
    generate_file(filepath);
    // Open the file in O_RDWR mode.
    // System call open returns the file descriptor.
    int descriptor = open(filepath, O_RDWR);
    // Handle an opening failure.
    if(descriptor == -1)
    {
        printf("Fail to open file.\n");
        return -1;
    }
    // Determine the string length.
    int string_len = strlen(my_string);
    // System call fstat utilizes structures stat.
    // Create an instance of this structure.
    struct stat info;
    // Retrieve information about the file using its descriptor.
    int fstat_r = fstat(descriptor, &info);
    // Check fstat returned error.
    if(fstat_r == -1)
    {
        printf("Error occurred while fstat() using.\n");
        close(descriptor);
        return -1;
    }
    // Determine the size of file, in bytes.
    int file_size = info.st_size;
    // Create new mapping in the virtual address space.
    char* area = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
    // Handle a mapping failure.
    if(area == -1)
    {
        printf("Fail to create new mapping.");
        close(descriptor);
        return -1;
    }
    // Truncate the file to string length.
    ftruncate(descriptor, string_len);
    // Copy new string to the mapped area.
    strncpy(area, my_string, string_len);
    // Delete the mapping.
    munmap(my_string, string_len);
    close(descriptor);
    return 0;
}
