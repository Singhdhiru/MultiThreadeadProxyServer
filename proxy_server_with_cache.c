#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <time.h>
#include <errno.h>
#include<pthread.h>
#include<semaphore.h>
// Need to link with Winsock Library
#pragma comment(lib, "ws2_32.lib")
// * typedef struct cache_element with cache_element
typedef struct cache_element cache_element;
#define MAX_CLIENT = 10; // Total number of clients

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


cache_element* head; //* pionter to the head of the LRU cache list
int size;            //* size of the LRU cache list

int main(){
    
}