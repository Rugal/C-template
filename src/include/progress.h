#ifndef PROGRESS_H
#define PROGRESS_H

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#include "Color.h"

/*
  Recommend to use ms = 60
 */
int printBraille(int ms)
{
  setlocale(LC_CTYPE, "");
  setbuf(stdout, NULL);

  const char *const braille[] = {"⠧", "⠇", "⠏", "⠋", "⠉", "⠙", "⠹", "⠸", "⠼", "⠴", "⠤", "⠦"};
  const int length = 12;
  const struct timespec timer = {0, ms * 1000000};

  for (int i = 0; 1; ++i)
  {
    i %= length;
    printf("%s%s%s%s%s", YELLOW.fg, BOLD.fg, braille[i], BOLD.bg, RESET.fg);
    if (nanosleep(&timer, NULL) < 0)
    {
      printf("Nano sleep system call failed \n");
      return -1;
    }
    printf("\b");
  }
  return 0;
}

/*
  Recommend to use ms = 60
 */
int printMoon(int ms)
{
  setlocale(LC_CTYPE, "");
  setbuf(stdout, NULL);

  const int length = 8;
  const int base = 0x1f311; // moon
  const struct timespec timer = {0, ms * 1000000};

  for (int i = 0; 1; ++i)
  {
    i %= length;
    printf("%lc", base + i);
    if (nanosleep(&timer, NULL) < 0)
    {
      printf("Nano sleep system call failed \n");
      return -1;
    }
    printf("\b\b");
  }
  return 0;
}

#endif
