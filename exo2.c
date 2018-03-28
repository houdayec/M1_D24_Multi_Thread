#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Function executed by the thread
void *thread_function(void *x_variable){
  printf("Waiting 2 secs\n");
  // Doing a malloc to save the PID value in memory
  pthread_t *TID = (pthread_t*) malloc(sizeof(pthread_t));
  *TID = pthread_self(); // Get its own TID
  printf("My PID from thread_function : %d \n", *TID);
  sleep(0.5);
  pthread_exit((void*)TID); // Return a value
}

int main(int argc, char const *argv[]){
  int tmp;
  void *pid;
  pthread_t thread;

  // Loop to create threads
  for(int i = 0; i < 2; i++){

    printf("je cree %d \n",thread);

    // Créer un thread non joignable;
    // 1st WAY
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create a new thread
    pthread_create(&thread, &attr, thread_function, NULL);

    // 2nd WAY but we need to remove setdetachstate
    //pthread_detach(thread);


    // Wait for the thread to finish its function
    pthread_join(thread, &pid);
    tmp=*((int *)pid);
    printf("PID du thread index %d: %d \n", i, tmp);

  }

}
