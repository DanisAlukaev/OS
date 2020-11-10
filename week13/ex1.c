// BS19-02 Alukaev Danis
// Task 1.

// Implementation of Deadlock Detection Algorithm provided on slide 39 of the Week 13 - Lecture.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Open input and output files.
    FILE *input = fopen("input.txt","r");
    FILE *output = fopen("output.txt","w");
    // A variable n stores the number of processes,
    // and a variable m - number of resources.
    int n, m;
    // Read values of n and m.
    fscanf(input, "%d %d", &n, &m);
    // Initialize auxiliary arrays used in algorithm:
    // E is the existing resource vector;
    // A is the available resource vector;
    // C is the current allocation matrix;
    // R is the request matrix.
    int E[m], A[m], C[n][m], R[n][m];
    // Filling in the existing resource vector.
    for(int i=0; i<m; i++)
        fscanf(input, "%d", &E[i]);
    // Filling in the available resource vector.
    for(int i=0; i<m; i++)
        fscanf(input, "%d", &A[i]);
    // Filling in the current allocation matrix.
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            fscanf(input, "%d", &C[i][j]);
    // Filling in the request matrix.
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            fscanf(input, "%d", &R[i][j]);
    // Initialize array of markers for processes (see step 1 on slide 39).
    int markers[n];
    // Set 0 as a default value for all processes.
    for(int i=0; i<n; i++)
        markers[i] = 0;
    // Store number of executed processes.
    int executed=0;
    // n iteration guarantees that all processes will attempt to start.
    for(int i=0; i<n; i++)
    {
        // Look for unmarked process Pi, for which the i-th row of R is less than or equal to A.
        int index = -1;
        for(int j=0; j<n; j++)
        {
            // Process is unmarked.
            if(!markers[j])
            {
                // Check whether the condition is met.
                int match = 1;
                for(int r=0; r<m; r++)
                {
                    // An i-th row of R is not less than or equal to A.
                    if(R[j][r]>A[r])
                    {
                        // Process does not match requirements.
                        match = 0;
                        break;
                    }
                }
                if(!match)
                    // Consider next process.
                    continue;
                // Save an index of the process.
                index = j;
                break;
            }
        }
        // Check whether algorithm failed to determine any process.
        if(index == -1)
            break;
        // Add the i-th row of C to A (step 2.1).
        for(int j=0; j<m; j++)
            A[j] += C[index][j];
        // Mark the process.
        markers[index] = 1;
        // Increment counter.
        executed++;
    }
    // Output results.
    if(executed == n)
        fprintf(output, "No deadlock is detected.");
    else
    {
        fprintf(output, "Processes ");
        for(int i=0; i<n; i++)
            if(!markers[i])
                fprintf(output, "%d ", i+1);
        fprintf(output, "were deadlocked.");
    }
    // Close files.
    fclose(input);
    fclose(output);
    return 0;
}
