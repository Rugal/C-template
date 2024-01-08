#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "chopstick.h"
#include "log4c.h"
#include "person.h"

Person* createPerson(int index) {
  Person *data = malloc(sizeof(Person));
  LOG_TRACE("Create person [%d]", index)
  assert(NULL != data);
  bzero(data, sizeof(Person));
  data->index = index;
  return data;
}

void deletePerson(Person* data) {
  assert(NULL != data);
  LOG_TRACE("Delete person [%d]", data->index)
  free(data);
}
