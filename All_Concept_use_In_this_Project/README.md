## what is the meaning of pthread_t ?
**A simple C program to demonstrate use of pthread basic functions**
```
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Let us create a global variable to change it in threads
int g = 0;

// The function to be executed by all threads
void* myThreadFun(void* vargp)
{
    // Store the value argument passed to this thread
    int myid = getpid();

    // Let us create a static variable to observe its
    // changes
    static int s = 0;

    // Change static and global variables
    ++s;
    ++g;

    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid,
           ++s, ++g);
}

int main()
{
    int i;
    pthread_t tid;
    //we declare a variable called thread_id, which is of type pthread_t, which is an integer 
    used to identify the  Let us create three threads 
    After declaring thread_id, we call pthread_create() function to create a thread.
    for (i = 0; i < 3; i++)
        pthread_create(&tid, NULL, myThreadFun, NULL);

    pthread_exit(NULL);
    return 0;
}
```
**Pthread_create() working**
1. The pthread_create() function is used to create a new Thread.
2. Its take four argument in pthread_create function.
    ###
    * The first argument is a pointer to thread_id which is set by this function. 
    * The second argument specifies attributes. If the value is NULL, then default attributes shall be used. 
    * The third argument is name of function to be executed for the thread to be created. 
    * The fourth argument is used to pass arguments to the function, myThreadFun. 