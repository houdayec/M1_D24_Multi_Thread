#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Global variables
int nbThreads = 3;
int cont = 0;

// Function executed by the thread
void *thread_function(void *arg){

    pthread_mutex_t* mutex = ((pthread_mutex_t *) arg);
    pthread_mutex_lock(mutex); // Wait until it gets the mutex
    pthread_t *TID = pthread_self(); // Get its own TID
    printf("Mutex taken by TID : %d\n", (int)*TID);
    sleep(3);
    pthread_mutex_unlock(mutex); // Release the mutex

}

int main(int argc, char const *argv[]){

    pthread_mutex_t lock;

    // Mutex init
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex init failed \n");
        return 1;
    }

    // Get the mutex by locking - wait until its possible
    pthread_mutex_lock(&lock);

    pthread_t thread_pool[3];

    // Loop to create threads
    for(int i = 0; i < nbThreads; i++){

        pthread_create(&thread_pool[i], NULL, thread_function, (void *)&lock);

    }
    sleep(3);
    // Release the mutex
    pthread_mutex_unlock(&lock);

    for(int i = 0; i < nbThreads; i++){

        pthread_join(thread_pool[i], NULL);

    }


}
