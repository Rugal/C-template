#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "log4c.h"
// #include "progress.h"
// #include "Thread.h"

#define NUMBER 5
#define NUM_THREADS 2
#define LEFT(i) ((i) % NUMBER)
#define RIGHT(i) LEFT(i + 1)

//Set overall log level
int log4c_level = LOG4C_ALL;

typedef struct
{
  int index;
  int *resource;
  pthread_mutex_t *mutex;
} ThreadData;

bool pick(const int i, ThreadData *parameter)
{
  LOG_DEBUG("Try to get mutex [%d]", i);
  pthread_mutex_lock(&parameter->mutex[i]);
  sleep(1);
  if (parameter->resource[i] != -1)
  {
    // this chopstick is taken
    LOG_DEBUG("Chopstick [%d] is taken", i);
    pthread_mutex_unlock(&parameter->mutex[i]);
    return false;
  }
  // this chopstick is available
  LOG_DEBUG("Chopstick [%d] is available", i);
  parameter->resource[i] = parameter->index;
  pthread_mutex_unlock(&parameter->mutex[i]);
  return true;
}

void put(const int i, ThreadData *parameter)
{
  pthread_mutex_lock(&parameter->mutex[i]);
  parameter->resource[i] = -1;
  pthread_mutex_unlock(&parameter->mutex[i]);
}

void runtime(void *input)
{
  ThreadData *parameter = (ThreadData *)input;
  while (true)
  {
    //pick left
    sleep(1);
    LOG_INFO("[%d] tries to get left chopstick [%d]", parameter->index, LEFT(parameter->index));
    while (!pick(LEFT(parameter->index), parameter))
      ;
    LOG_INFO("[%d] gets left chopstick [%d]", parameter->index, LEFT(parameter->index));
    sleep(1);
    //pick right
    LOG_INFO("[%d] tries to get right chopstick [%d]", parameter->index, RIGHT(parameter->index));
    while (!pick(RIGHT(parameter->index), parameter))
      ;
    LOG_INFO("[%d] gets right chopstick [%d]", parameter->index, RIGHT(parameter->index));
    sleep(1);
    LOG_INFO("[%d] is eating", parameter->index);
    sleep(3);
    LOG_INFO("[%d] put left chopstick [%d]", parameter->index, LEFT(parameter->index));
    put(LEFT(parameter->index), parameter);
    LOG_INFO("[%d] put right chopstick [%d]", parameter->index, RIGHT(parameter->index));
    put(RIGHT(parameter->index), parameter);
  }
}

int main()
{
  pthread_mutex_t mutex[NUMBER];
  int resource[NUMBER];
  ThreadData data[NUMBER];
  for (int i = 0; i < NUMBER; ++i)
  {
    bzero(&data[i], sizeof(ThreadData));
    resource[i] = 0;
    pthread_mutex_init(&mutex[i], NULL);
    data[i].index = i;
    data[i].mutex = &mutex;
    data[i].resource = &resource;
  }

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUMBER; ++i)
  {
    pthread_create(&threads[i], NULL, runtime, &data[i]);
  }

  for (int i = 0; i < NUMBER; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  destroyThreadData(&data);
  return 0;
}
