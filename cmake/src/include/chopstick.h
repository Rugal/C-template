#ifndef CHOPSTICK_T
#define CHOPSTICK_T

#include <stdbool.h>
#include <pthread.h>

typedef struct
{
  int index;
  int usedBy;
  pthread_mutex_t *mutex;
} Chopstick;

Chopstick* createChopstick(int index);

void deleteChopstick(Chopstick* data);

bool pick(const int i, Chopstick *c);

void put(Chopstick* c);

#endif
