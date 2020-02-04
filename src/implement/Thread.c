#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "log4c.h"
#include "Thread.h"

ThreadData *createThreadData()
{
  ThreadData *data = malloc(sizeof(ThreadData));
  data->counter = 0;
  pthread_mutex_init(&data->mutex, NULL);
  pthread_cond_init(&data->condition, NULL);
  return data;
}

void destroyThreadData(ThreadData *data)
{
  assert(data != NULL);
  data->counter = 0;
  pthread_mutex_destroy(&data->mutex);
  pthread_cond_destroy(&data->condition);
  free(data);
}

void *consumer(void *input)
{
  ThreadData *data = (ThreadData *)input;
  LOG_INFO("Consumer start");
  while (true)
  {
    pthread_mutex_lock(&data->mutex);
    LOG_INFO("Now we have %d", data->counter);
    if (data->counter)
    {
      LOG_INFO("Consume");
      sleep(1);
      data->counter = 0;
      pthread_cond_signal(&data->condition);
      LOG_INFO("Consumption done");
    }
    else
    {
      LOG_INFO("Wait for production");
      pthread_cond_wait(&data->condition, &data->mutex);
      LOG_INFO("Get production signal");
    }
    pthread_mutex_unlock(&data->mutex);
  }
  pthread_exit(NULL);
}

void *producer(void *input)
{
  ThreadData *data = (ThreadData *)input;
  LOG_INFO("Producer start");
  while (true)
  {
    pthread_mutex_lock(&data->mutex);
    LOG_INFO("Now we have %d", data->counter);
    if (data->counter)
    {
      LOG_INFO("Wait for consumption");
      pthread_cond_wait(&data->condition, &data->mutex);
      LOG_INFO("Get consumption signal");
    }
    else
    {
      LOG_INFO("Produce");
      sleep(1);
      data->counter = 1;
      pthread_cond_signal(&data->condition);
      LOG_INFO("Production done");
    }
    pthread_mutex_unlock(&data->mutex);
  }
  pthread_exit(NULL);
}
