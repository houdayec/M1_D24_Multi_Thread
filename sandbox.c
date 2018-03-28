#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<errno.h>


pthread_mutex_t mutex;
pthread_cond_t cv;
int cpt = 0;

void* th(void* arg){
  printf("Fille %lu\n",pthread_self() );
  for (int i = 0; i < 4; i++) {
      pthread_mutex_lock(&mutex);
      cpt ++;
      if (cpt >= 3) {
        pthread_cond_signal(&cv);
      }
      pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

void* th2(void* arg){
  printf("Fille %lu\n",pthread_self() );
  for (int i = 0; i < 4; i++) {
      pthread_mutex_lock(&mutex);
      cpt ++;
      if (cpt >= 3) {
        pthread_cond_signal(&cv);
      }
      pthread_mutex_unlock(&mutex);
      sleep(1);
  }
  pthread_exit(NULL);
}

void* egale(void* arg){
  struct timespec ts;
  pthread_mutex_lock(&mutex);

  ts.tv_sec = time(NULL)+3;
  pthread_cond_timedwait(&cv, &mutex, &ts);
  printf("cpt = %d\n",cpt);

  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}


int main(int argc, char const *argv[]) {
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cv, NULL);

  pthread_mutex_lock(&mutex);

  pthread_t id, id2, id3;
  pthread_create(&id3, NULL, egale, NULL);
  pthread_create(&id, NULL, th, NULL);
  pthread_create(&id2, NULL, th2, NULL);

  pthread_mutex_unlock(&mutex);
  pthread_join(id3, NULL);
  return 0;
}
