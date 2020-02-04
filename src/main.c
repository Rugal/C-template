#include <pthread.h>
#include <unistd.h>

#include "log4c.h"
#include "Thread.h"

#define NUM_THREADS 2

//Set overall log level
int log4c_level = LOG4C_ALL;

int main()
{
  ThreadData *data = createThreadData();

  pthread_t threads[NUM_THREADS];

  pthread_create(&threads[0], NULL, producer, (void *)data);
  pthread_create(&threads[1], NULL, consumer, (void *)data);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  destroyThreadData(&data);
  return 0;
}
