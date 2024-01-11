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

bool pick(const int i, Chopstick *c) {
  assert(NULL != c);
  LOG_DEBUG("[%d] Try to get mutex [%d]", i, c->index);
  pthread_mutex_lock(c->mutex);
  if (c->usedBy != -1) {
    // this chopstick is taken
    LOG_DEBUG("Chopstick [%d] is taken by [%d]", c->index, c->usedBy);
    pthread_mutex_unlock(c->mutex);
    return false;
  }
  // this chopstick is available
  LOG_DEBUG("Chopstick [%d] is available", c->index);
  c->usedBy = i;
  LOG_DEBUG("[%d] take chopstick [%d]", c->usedBy, c->index);
  pthread_mutex_unlock(c->mutex);
  return true;
}

void put(Chopstick* c) {
  assert(NULL != c);
  LOG_DEBUG("[%d] try to put chopstick [%d] back", c->usedBy, c->index);
  pthread_mutex_lock(c->mutex);
  LOG_DEBUG("[%d] put chopstick [%d] back", c->usedBy, c->index);
  c->usedBy = -1;
  pthread_mutex_unlock(c->mutex);
}
