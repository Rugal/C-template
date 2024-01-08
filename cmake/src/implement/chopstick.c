#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "log4c.h"
#include "chopstick.h"

Chopstick* createChopstick(int index) {
  Chopstick *data = malloc(sizeof(Chopstick));
  LOG_TRACE("Create chopstick [%d]", index)
  assert(NULL != data);
  bzero(data, sizeof(Chopstick));
  data->index = index;
  data->usedBy = -1;
  pthread_mutex_t* m = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(m, NULL);
  data->mutex = m;
  return data;
}

void deleteChopstick(Chopstick* data) {
  assert(NULL != data);
  LOG_TRACE("Delete chopstick [%d]", data->index)
  pthread_mutex_destroy(data->mutex);
  free(data);
}
