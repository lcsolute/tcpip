#include <pthread.h>
#include <stdio.h>

#define NUM_THREAD 100

void *thread_inc(void *arg);
void *thread_des(void *arg);

long long num;
pthread_mutex_t mutex; // 操作系统创建

int main(void) {
  pthread_t t_id[NUM_THREAD];
  int i;

  pthread_mutex_init(&mutex, NULL);

  for (i = 0; i < NUM_THREAD; i++) {
    if (i % 2)
      pthread_create(&t_id[i], NULL, thread_inc, NULL);
    else
      pthread_create(&t_id[i], NULL, thread_des, NULL);
  }

  for (i = 0; i < NUM_THREAD; i++)
    pthread_join(t_id[i], NULL);

  printf("result: %lld \n", num);
  pthread_mutex_destroy(&mutex);
  return 0;
}

void *thread_inc(void *arg) {
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < 500000; i++)
    num += 1;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *thread_des(void *arg) {
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < 500000; i++)
    num -= 1;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
