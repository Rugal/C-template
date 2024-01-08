#ifndef PERSON_T
#define PERSON_T

#include <stdbool.h>

#include "chopstick.h"

typedef struct
{
  int index;
  Chopstick *left;
  Chopstick *right;
} Person;

Person *createPerson(int index);

void deletePerson(Person *data);

#endif
