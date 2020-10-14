// BS19-02 Alukaev Danis
// Task 1.

/*
Sample outputs:

Specify number of frames: 10
Specify clock interval: 4
Hits number: 10.
Misses number: 990.
Hit/Miss ratio: 0.010101.

Specify number of frames: 50
Specify clock interval: 4
Hits number: 55.
Misses number: 945.
Hit/Miss ratio: 0.058201.

Specify number of frames: 100
Specify clock interval: 4
Hits number: 92.
Misses number: 908.
Hit/Miss ratio: 0.101322.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure representing page frame.
typedef struct frame
{
    // Page number.
    unsigned int page;
    // Counter.
    unsigned int age;
    // Referenced bit.
    unsigned int R;
} frame_t;

/**
 * Returns the index of page with received number.
 *
 * @param page - page number.
 * @param frames - an array of page frames.
 * @param numFrames - the number of frames.
 */
int findPage(int page, frame_t frames[], int numFrames)
{
    for(int i=0; i<numFrames; i++)
        if(frames[i].page == page)
            return i;
    return -1;
}

/**
 * Updates the counters of frames.
 *
 * @param frames - an array of page frames.
 * @param numFrames - the number of frames.
 */
void updateAge(frame_t frames[], int numFrames)
{
    for(int i=0; i<numFrames; i++)
    {
        // The counters are shifted right 1 bit.
        frames[i].age = frames[i].age >> 1;
        // The R-bit is added to the leftmost bit.
        frames[i].age |= frames[i].R << 28;
        // Nullify all R-bits.
        frames[i].R = 0;
    }
}

/**
 * Returns the index of frame with the least counter.
 *
 * @param frames - an array of page frames.
 * @param numFrames - the number of frames.
 */
int indexLeastCounter(frame_t frames[], int numFrames)
{
    int leastAge = INT_MAX;
    int leastIndex = 0;
    for(int i=0; i<numFrames; i++)
    {
        if(frames[i].age < leastAge)
        {
            leastAge = frames[i].age;
            leastIndex = i;
        }
    }
    return leastIndex;
}

int main()
{
    int numFrames, numHits=0, numMisses=0, cTick=0, interval=1;

    // Set the number of frames and clock interval.
    printf("Specify number of frames: ");
    scanf("%d", &numFrames);
    printf("Specify clock interval: ");
    scanf("%d", &interval);

    // Array of frames.
    frame_t frames[numFrames];
    for(int i=0; i<numFrames; i++)
    {
        // Nullify all attributes.
        frames[i].age = 0;
        frames[i].page = -1;
        frames[i].R = 0;
    }

    // Open the input file.
    FILE *pageReferences = fopen("ex1.txt", "r");
    while(!feof(pageReferences))
    {
        // Determine the number of requested page.
        int page;
        fscanf(pageReferences, "%d", &page);
        // Check whether the page with such number is frames.
        int idPage = findPage(page, frames, numFrames);
        if(idPage != -1)
        {
            // Page was found.
            // Increment number of hits.
            numHits++;
            // Page was referenced
            frames[idPage].R = 1;
        }
        else
        {
            // Page was not found.
            // Increment number of misses.
            numMisses++;
            // Find the frame with least counter.
            int toReplace = indexLeastCounter(frames, numFrames);
            // Update the page number.
            frames[toReplace].page = page;
            // Nullify the age of the frame.
            frames[toReplace].age = 1 << 28;
            // Page was referenced
            frames[toReplace].R = 1;
        }
        // Update counters for all frames.
        if(cTick % interval == 0)
            updateAge(frames, numFrames);
        // Clock ticked.
        cTick++;
    }
    // Compute hits/miss ratio.
    float ratio = (float)numHits/numMisses;
    printf("Hits number: %d.\nMisses number: %d.\nHit/Miss ratio: %f.\n", numHits, numMisses, ratio);
    return 0;
}
