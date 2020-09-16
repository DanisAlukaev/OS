// BS19-02 Alukaev Danis
// Task 3.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// define capacity of a buffer
#define CAPACITY 5

// global variables to implement sleep and wakeup routine
// 0 stands for sleep
// 1 stands for wakeup
int producer_state = 1;
int consumer_state = 0;

// let variable buffer displays number of items in buffer
int buffer=0;

// implementation refers to https://en.wikipedia.org/wiki/Producer–consumer_problem

void *producer()
{
    while(1)
    {
        if (producer_state)
        {
            printf("Turn of producer. \n");
            fflush(stdout);
            if(buffer==CAPACITY)
            {
                producer_state=0;
                printf("Producer starts sleeping.\n");
                fflush(stdout);
            }

            buffer++;
            printf("Item produced. Buffer: %d/%d \n",buffer,CAPACITY);
            fflush(stdout);

            if(buffer==1)
                consumer_state=1;

            if(buffer<0)
            {
                printf("Error: items<0. \n");
                fflush(stdout);
            }
            else if(buffer>CAPACITY)
            {
                printf("Error: items>CAPACITY. \n");
                fflush(stdout);
            }
        }
    }
}

void *consumer()
{
    while(1)
    {
        if (consumer_state)
        {
            printf("Turn of customer. \n");
            fflush(stdout);
            if(buffer==0)
            {
                consumer_state=0;
                printf("Customer starts sleeping.\n");
                fflush(stdout);
            }

            buffer--;
            printf("Item taken. Buffer: %d/%d \n",buffer,CAPACITY);
            fflush(stdout);

            if(buffer==CAPACITY-1)
                producer_state=1;

            if(buffer<0)
            {
                printf("Error: items<0. \n");
                fflush(stdout);
            }
            else if(buffer>CAPACITY)
            {
                printf("Error: items>CAPACITY. \n");
                fflush(stdout);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // initialize and run threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);
    return 0;
}
