// BS19-02 Alukaev Danis
// Task 3.

// In first run of implementation without using synchronization primitives the race condition manifests on the 587-th iteration.
// This implementation (with using synchronization primitives) refers to https://en.wikipedia.org/wiki/Producer–consumer_problem

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// define capacity of a buffer
#define CAPACITY 5

// initialize buffer of capacity CAPACITY
int buffer[CAPACITY];
// number of items in buffer
int items=0;
// create new instances of mutex and conditional variables
pthread_mutex_t mutex;
pthread_cond_t producer_s,consumer_s;

void *producer()
{
    while(1)
    {
        // lock mutex by producer thread
        pthread_mutex_lock(&mutex);
        if(items==CAPACITY-1)
        {
            // producer starts sleeping
            pthread_cond_wait(&producer_s, &mutex);
            // print state of producer
            printf("Producer starts sleeping.\n");
            fflush(stdout);
        }
        // modify buffer (0 stands for presence of item in buffer)
        buffer[items]=0;
        // increase item counter
        items++;

        // print state of producer
        printf("Item produced. Buffer: %d/%d \n",items,CAPACITY);
        fflush(stdout);

        if(items==1)
        {
            // wake up consumer
        }
        // unlock consumer thread
        pthread_cond_signal(&consumer_s);
        // unlock mutex
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer()
{
    while(1)
    {
        // lock mutex by consumer thread
        pthread_mutex_lock(&mutex);
        if(items==0)
        {
            // consumer starts sleeping
            pthread_cond_wait(&consumer_s, &mutex);
            // print state of producer
            printf("Consumer starts sleeping.\n");
            fflush(stdout);
        }
        // decrease item counter
        items--;
        // modify buffer (-1 stands for absence of item in buffer)
        buffer[items]=-1;

        // print state of producer
        printf("Item taken. Buffer: %d/%d \n",items,CAPACITY);
        fflush(stdout);

        if(items==CAPACITY-1)
        {
            // wake up producer
        }
        // unlock producer thread
        pthread_cond_signal(&producer_s);
        // unlock mutex
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t producer_thread, consumer_thread;
    // fill buffer
    // -1 stands for abscence of item in buffer
    // 0 stands for presence of item in buffer
    for(int i=0; i<CAPACITY; i++)
        buffer[items]=-1;
    // initialize conditional variables and mutex
    pthread_cond_init(&producer_s, NULL);
    pthread_cond_init(&consumer_s, NULL);
    pthread_mutex_init(&mutex, NULL);
    // create producer and consumer threads
    pthread_create(&producer_thread, NULL, &producer, NULL);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);
    // wait for the producer and consumer threads to terminate
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    // destroy conditional variables and mutex
    pthread_cond_destroy(&producer_s);
    pthread_cond_destroy(&consumer_s);
    pthread_mutex_destroy(&mutex);
    return 0;
}
