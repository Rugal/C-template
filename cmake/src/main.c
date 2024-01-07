#include <stdio.h>
#include "log4c.h"

int log4c_level = LOG4C_ALL;

int main()
{
  printf("Rugal\n");
  LOG_ERROR("Bernstein");
  return 0;
}
