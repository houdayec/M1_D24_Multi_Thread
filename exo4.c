#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Global variables
int nbThreads = 3;
int count = 0;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock;

// Function executed by the thread
void *thread_increment(/*void *arg*/){

    // If we pass the mutex as an param from pthread_create
    //pthread_mutex_t* mutex = ((pthread_mutex_t *) arg);
    for(int i = 0; i < 4; i++){
        // Get the mutex - wait until it gets it
        pthread_mutex_lock(&lock);
        printf("Thread %d took the mutex ", pthread_self());
        count++;
        printf("Value count : %d\n", count);
        if(count == 3){
            // Send a signal to the thread
            printf("Send signal, value reached\n");
            pthread_cond_signal(&cv);
        }
        // Release the mutex
        pthread_mutex_unlock(&lock); // Release the mutex
    }
    pthread_exit(NULL);
}

// Function executed by the thread
void *thread_increment_with_sleep(){

    // If we pass the mutex as an param from pthread_create
    //pthread_mutex_t* mutex = ((pthread_mutex_t *) arg);
    for(int i = 0; i < 4; i++){
        // Get the mutex - wait until it gets it
        pthread_mutex_lock(&lock);
        printf("Thread %d took the mutex ", pthread_self());
        count++;
        printf("Value count : %d\n", count);
        if(count == 3){
            // Send a signal to the thread
            printf("Send signal, value reached\n");
            pthread_cond_signal(&cv);
        }
        printf("Value count : %d\n", count);
        // Release the mutex
        pthread_mutex_unlock(&lock); // Release the mutex
        printf("Thread sleep for 2 seconds\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

void *thread_wait(){

    // Get the mutex - wait until it gets it
    //pthread_mutex_lock(&lock);
    if(count < 3){
        printf("Waiting for counter to be equal to three\n");
        pthread_cond_wait(&cv,&lock);
    }
    printf("Count has reached 3 !\n");
    //pthread_mutex_unlock(&lock);
    pthread_exit(NULL);

}

int main(int argc, char const *argv[]){

    pthread_t thread_pool[3];

    // Mutex init
    if(pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex init failed \n");
        return 1;
    }

    // Conditionnal variable init
    if(pthread_cond_init(&cv, NULL) != 0){
        printf("CV init failed \n");
        return 2;
    }


    // Get the mutex by locking - wait until its possible
    pthread_mutex_lock(&lock);
    pthread_create(&thread_pool[2], NULL, thread_wait, NULL);

    for(int i = 0; i < nbThreads; i++){
        switch(i){
            case 0:
                pthread_create(&thread_pool[i], NULL, thread_increment, NULL);
            break;
            case 1:
                pthread_create(&thread_pool[i], NULL, thread_increment_with_sleep, NULL);
            break;
            case 2:
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    for(int i = 0; i < nbThreads; i++){
        if(i == 2) // If it is thread n°3
            pthread_join(thread_pool[i], NULL);
    }
}
