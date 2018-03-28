#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int x = 0;
int pid = 0;

// Function executed by the thread
void *thread_function(void *x_variable){
  pid_t TID = pthread_self();
  printf("Current PID : %d \n", TID);
  pthread_exit(0);
}

// Main function
int main(int argc, char const *argv[]){

// Creation of 1000 threads
for(int i = 0; i < 1000; i++){

  // Checking if current thread is a child
  //if((pid = fork()) == 0){
    //fprintf("This is a child thread with PID %d\n", pid);
    pthread_t thread;
    if(pthread_create(&thread, NULL, thread_function, &x)){
      printf("Error creating the child thread \n");
      return 1; // End program with code 1
    }
    pthread_join(thread, NULL);
  /*}else{
    printf("Waiting for the child to finish \n");
    //waitpid(pid, NULL, 0);
  }*/
}
}
