#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
// * typedef struct cache_element with cache_element
typedef struct cache_element cache_element;
#define MAX_CLIENT  10 // Total number of clients

struct cache_element{
    char* data;         //data stores response
    int len;          //length of data i.e.. sizeof(data)...
    char* url;        //url stores the request
	time_t lru_time_track;    //lru_time_track stores the latest time the element is  accesed
    cache_element* next;    //pointer to next element
};
cache_element* find(char* data, int size, char* url);
int add(char* data, int size, char* url);
void remove_cache_element();

int port_number = 8080;  //* Default port number
int proxy_socketId;      //* socket id for proxy server
pthread_t tid[MAX_CLIENT]; //* thread id for each client that is connected to the proxy server and store in array
sem_t semaphore;          //* if client requests exceeds the max_clients this seamaphore puts the
                         //*waiting threads to sleep and wakes them when traffic on queue decreases

//*sem_t cache_lock;
pthread_mutex_t lock;     //* mutex lock to synchronize access to the cache


cache_element* head; //* pointer to the head of the LRU cache list
int size;            //* size of the LRU cache list

int main(int argc, char * argv[]){
    int client_socketId, client_length; // client_socketId stores the socket id of the client
    struct sockaddr client_address, socket_address; // client_address and socket_address stores the address of the client and server
    sem_int(&semaphore, 0, 1); // intialize the semaphore with 0 and 1
    pthread_mutex_init(&lock, NULL); // intialize the mutex lock

    if(argv == 2){ // checking whether two argument is passed or not
        port_number = atoi(argv[1]);
    }
    else{
        printf("Too few arguments\n");
        exit(1);
    }
    printf("Setting up the proxy sever on port_number : %d\n", port_number);
    // creating proxy server
    proxy_socketId = socket(AF_INET, SOCK_STREAM, 0); // creating a socket for proxy server
    if(proxy_socketId < 0){
        printf("Error in creating socket\n");
        exit(1);
    }
    

}