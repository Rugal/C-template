#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
// #include <unistd.h>

// #include "progress.h"
#include "chopstick.h"
#include "log4c.h"
#include "person.h"

#define NUMBER 5
#define NUM_THREADS 5
#define LEFT(i) ((i) % NUMBER)
#define RIGHT(i) LEFT(i + 1)

//Set overall log level
int log4c_level = LOG4C_ALL;

bool pick(const int i, Chopstick *c) {
  assert(NULL != c);
  LOG_DEBUG("Try to get mutex [%d]", i);
  pthread_mutex_lock(c->mutex);
  // sleep(1);
  if (c->usedBy != -1) {
    // this chopstick is taken
    LOG_DEBUG("Chopstick [%d] is taken by [%d]", c->index, c->usedBy);
    pthread_mutex_unlock(c->mutex);
    return false;
  }
  // this chopstick is available
  LOG_DEBUG("Chopstick [%d] is available", i);
  c->usedBy = i;
  LOG_DEBUG("[%d] take chopstick [%d]", c->usedBy, c->index);
  pthread_mutex_unlock(c->mutex);
  return true;
}

void put(Chopstick* c) {
  assert(NULL != c);
  pthread_mutex_lock(c->mutex);
  LOG_DEBUG("[%d] put chopstick [%d] back", c->usedBy, c->index);
  c->usedBy = -1;
  pthread_mutex_unlock(c->mutex);
}

void* runtime(void* input) {
  assert(NULL != input);
  // Person* p = (Person*) input; // single person data
  pthread_exit(0);
}

int main() {
  Person* ps[NUMBER];
  Chopstick* cs[NUMBER];
  for (int i = 0; i < NUMBER; ++i) {
    cs[i] = createChopstick(i);
  }
  for (int i = 0; i < NUMBER; ++i) {
    ps[i] = createPerson(i);
    ps[i]->left = cs[LEFT(i)];
    ps[i]->right = cs[RIGHT(i)];
  }

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUMBER; ++i) {
    pthread_create(&threads[i], NULL, runtime, ps[i]);
  }

  for (int i = 0; i < NUMBER; ++i) {
    pthread_join(threads[i], NULL);
    deleteChopstick(cs[i]);
    deletePerson(ps[i]);
  }

  return 0;
}
