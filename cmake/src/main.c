#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
// #include <unistd.h>

#include "chopstick.h"
#include "log4c.h"
#include "person.h"

#define NUMBER 5
#define NUM_THREADS 5
#define LEFT(i) ((i) % NUMBER)
#define RIGHT(i) LEFT(i + 1)

//Set overall log level
int log4c_level = LOG4C_INFO;

void* runtime(void* input) {
  assert(NULL != input);
  Person* p = (Person*) input;
  while(true) {
    if (pick(p->index, p->left) == false) {
      // unable to pick left, repeat if unable to pick
      continue;
    }

    if (pick(p->index, p->right) == false) {
      // unable to pick right, release left as well
      put(p->left);
      continue;
    }
    LOG_INFO("Philosopher [%d] start eating", p->index);
    int t = rand() % 5;
    while(t-- > 0) {
      LOG_INFO("Philosopher [%d] is still eating", p->index);
      sleep(1);
    }
    LOG_INFO("Philosopher [%d] eat completed", p->index);
    put(p->left);
    put(p->right);
  }
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
    LOG_INFO("Thread [%d] start", ps[i]->index);
    pthread_create(&threads[i], NULL, runtime, ps[i]);
  }

  for (int i = 0; i < NUMBER; ++i) {
    pthread_join(threads[i], NULL);
    LOG_INFO("Thread [%d] stop", ps[i]->index);
    deleteChopstick(cs[i]);
    deletePerson(ps[i]);
  }

  return 0;
}
