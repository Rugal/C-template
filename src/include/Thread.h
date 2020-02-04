#ifndef THREAD_T
#define THREAD_T

#include <pthread.h>

typedef struct
{
  int counter;
  pthread_cond_t condition;
  pthread_mutex_t mutex;
} ThreadData;

ThreadData *createThreadData();

void destroyThreadData(ThreadData *data);

void *consumer(void *input);

void *producer(void *input);

#endif
