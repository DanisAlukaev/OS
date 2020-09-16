// BS19-02 Alukaev Danis
// Task 1.

/*
The following program outputs:
1. By default:
This is the thread 448440128; created new thread (448435968) with number 0.
This is the thread 448440128; created new thread (440043264) with number 1.
This is the thread 448440128; created new thread (431650560) with number 2.
This is the thread 448440128; created new thread (423257856) with number 3.
This is the thread 448440128; created new thread (414865152) with number 4.
This is the thread 414865152 with number 4.
This is the thread 423257856 with number 3.
This is the thread 431650560 with number 2.
This is the thread 440043264 with number 1.
This is the thread 448435968 with number 0.

It seems that threads start execution using a LIFO policy. In other words, processes still
run in pseudo-parallel, but the order of execution is following: the latest created thread starts execution firs.t

2. For sequential version:
This is the thread 1643509568; created new thread (1643505408) with number 0.
This is the thread 1643505408 with number 0.
This is the thread 1643509568; created new thread (1643505408) with number 1.
This is the thread 1643505408 with number 1.
This is the thread 1643509568; created new thread (1643505408) with number 2.
This is the thread 1643505408 with number 2.
This is the thread 1643509568; created new thread (1643505408) with number 3.
This is the thread 1643505408 with number 3.
This is the thread 1643509568; created new thread (1643505408) with number 4.
This is the thread 1643505408 with number 4.

Using pthread_join() allows to execute threads sequentially, i.e.,
wait for the previous thread to terminate before starting the next one.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// let number of threads N be 5
#define N 5

pthread_t thread_id[N];

void *idThread(int i)
{
    // output thread's id and its number that is exactly iteration, on which this thread was created
    printf("This is the thread %d with number %d.\n",(int)pthread_self(),i);
    // terminate current thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    for (int i=0;i<N;i++)
    {
        // create new thread that executes idThread
        int rc = pthread_create(&thread_id[i],NULL,idThread,i);
        if(rc)
        {
            printf("\n ERROR: return code from pthread_create is %d.\n", rc);
            exit(1);
        }
        printf("This is the thread %d; created new thread (%d) with number %d.\n",(int)pthread_self(),(int)thread_id[i],i);
        // wait for the i-th thread to terminate
        // used to force the order to be strictly sequential
        pthread_join(thread_id[i],NULL); // commented by default
    }
    pthread_exit(NULL);
}
