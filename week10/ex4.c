// BS19-02 Alukaev Danis
// Task 4.

/*
Sample output:

Files file1, link1 have same i-node 287799.
*/

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main()
{
    // Open "tmp" directory.
    DIR *tmp = opendir("tmp/");
    // Check whether such a directory exists.
    if(tmp == NULL)
        return -1;
    // Readdir returns information about file in dirent structure.
    // Create instance of this structure to iterate over the files in the directory.
    struct dirent *f;
    // Store number of files in array.
    int n_files = 0;
    // Determine number of elements.
    while((f = readdir(tmp)) != NULL)
        n_files++;
    closedir(tmp);
    // Open "tmp" directory.
    tmp = opendir("tmp/");
    // Array with information about files in "tmp".
    struct dirent *arr_files[n_files];
    // Set starting index;
    int current = 0;
    // Create array to mark examined files.
    int examined[n_files];
    while((f = readdir(tmp)) != NULL)
    {
        // Store information about current file.
        arr_files[current] = f;
        // Store i-node as marker that the i-node of this file is not examined for a match.
        examined[current] = f -> d_ino;
        // Increment counter.
        current++;
    }
    for(int i = 0; i < n_files; i++)
    {
        // Flag that at least one file with the same i-node is found.
        int match = 0;
        for(int j = i+1; j < n_files; j++)
        {
            // Check whether i-nodes of files are equal.
            if(examined[j] != -1 && arr_files[i] -> d_ino == arr_files[j] -> d_ino)
            {
                if(match == 0)
                {
                    // At least one file with the same i-node is found.
                    match = 1;
                    printf("Files %s, %s", arr_files[i] -> d_name, arr_files[j] -> d_name);
                }
                else
                    printf(", %s", arr_files[j] -> d_name);
                // Mark file as examined.
                examined[j] = -1;
            }
        }
        // Display the i-node of a files.
        if(match == 1)
            printf(" have same i-node %d.\n", arr_files[i] -> d_ino);
    }
    closedir(tmp);
    return 0;
}