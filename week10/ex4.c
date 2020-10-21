// BS19-02 Alukaev Danis
// Task 4.

/*
Sample output:

Files file1, link1 have same i-node 287799.
*/

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define max_length 255

// Structure to keep track of files within the directory.
// Consists of array of i-nodes with a hard link count of two or more,
// array of strings made up of names of files splitted by ',',
// and number of such i-nodes.
typedef struct files
{
    // Array of i-nodes.
    int *i_nodes;
    // Array of names associated with i-nodes.
    int **names;
    // Number of entries.
    int number;

} files_t;

/**
 * Recursively explore directory and examine file to have i-node with a hard link count of two or more.
 *
 * @param path - path to the directory.
 * @param my_files - structure to keep track of files within the directory.
 */
void search_entire_directory(char *path, files_t *my_files)
{
    // Open current directory.
    DIR *current = opendir(path);
    // readdir returns information about file in dirent structure.
    // Create instance of this structure to iterate over the files in the directory.
    struct dirent *dirent_data;
    while((dirent_data = readdir(current)) != NULL)
    {
        // In case that current structure describes the file.
        if(dirent_data -> d_type != DT_DIR)
        {
            char path2file[max_length];
            strcpy(path2file, path);
            strcat(path2file, dirent_data -> d_name);
            // stat() returns information about file in stat structure.
            // Create instance of this structure to iterate over the files in the directory.
            struct stat stat_data;
            if (stat(path2file, &stat_data) != -1 && stat_data.st_nlink >= 2)
            {
                // Flag signalizing that file with such i-node is found.
                int match = 0;
                for(int i=0; i < my_files -> number; i++)
                {
                    // Check whether i-nodes of files are equal.
                    if(my_files -> i_nodes[i] == dirent_data -> d_ino)
                    {
                        // Set flag to 1.
                        match = 1;
                        // Add ", <filename>" to string.
                        strcat(my_files -> names[i], ", ");
                        strcat(my_files -> names[i], dirent_data -> d_name);
                        break;
                    }
                }
                // If files with such i-node was not found, then record it.
                if(!match)
                {
                    // Set i-node.
                    my_files -> i_nodes[my_files -> number] = dirent_data -> d_ino;
                    // Set name.
                    strcpy(my_files -> names[my_files -> number], dirent_data -> d_name);
                    // One more i-node was added.
                    my_files -> number++;
                }
            }
        }
        else
        {
            // Otherwise, it is the directory.
            // Ignore current and previous directories.
            if(strcmp(dirent_data -> d_name, ".") != 0
                    && strcmp(dirent_data -> d_name, "..") != 0)
            {
                // String to store a path to directory to be explored.
                char path2dir[max_length];
                // Construct path to this directory.
                strcpy(path2dir, path);
                strcat(path2dir, dirent_data -> d_name);
                strcat(path2dir, "/");
                // Examine files in this directory to have i-node with a hard link count of two or more
                search_entire_directory(path2dir, my_files);
            }
        }
    }
    closedir(current);
}

int main()
{
    // Open "tmp" directory.
    DIR *tmp = opendir("./tmp/");
    // Check whether such a directory exists.
    if(tmp == NULL)
    {
        printf("There is no such directory.");
        return -1;
    }
    // Readdir returns information about file in dirent structure.
    // Create instance of this structure to iterate over the files in the directory.
    struct dirent *f;
    // Store number of files in array.
    int n_files = 0;
    // Determine number of elements.
    while((f = readdir(tmp)) != NULL)
        n_files++;
    closedir(tmp);
    // Create instance of a structure to keep track of files with the same i-node values.
    files_t my_files;
    // Set first index to zero.
    my_files.number = 0;
    // Allocate memory for i-nodes.
    my_files.i_nodes = malloc(n_files * sizeof(int));
    my_files.names = malloc(n_files * sizeof(char*));
    for (int i = 0; i < n_files; i++)
        my_files.names[i] = malloc(max_length * sizeof(char));
    // Call function that passes through the directory and save files with the same i-node.
    search_entire_directory("./tmp/", &my_files);
    // Display files with the same i-node.
    for(int i=0; i < my_files.number; i++)
        printf("Files %s have same i-node %d.\n", my_files.names[i], my_files.i_nodes[i]);
    return 0;
}
