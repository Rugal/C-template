#ifndef LOG4C_H
#define LOG4C_H

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

enum Log4CLevel {
  LOG4C_ALL     = 0,
  LOG4C_TRACE   = 1,
  LOG4C_DEBUG   = 2,
  LOG4C_INFO    = 3,
  LOG4C_WARNING = 4,
  LOG4C_ERROR   = 5,
  LOG4C_OFF     = 6
};

static const char* LOG_NAME[] = {"ALL",
                                 "\033[0;37mTRACE\033[0m",
                                 "\033[0;36mDEBUG\033[0m",
                                 "\033[0;32mINFO\033[0m",
                                 "\033[0;35mWARN\033[0m",
                                 "\033[0;31mERROR\033[0m",
                                 "OFF"};

extern int log4c_level;

#define LOG(level, fmt, ...) \
  if (level >= log4c_level) { \
    fprintf(stderr, \
            "[%5s] %s @ %-15s#%4d: " fmt "\n", \
            LOG_NAME[level], \
            __func__, \
            __FILENAME__, \
            __LINE__, \
            ##__VA_ARGS__); \
  }

#define LOG_ALL(fmt, ...)   LOG(LOG4C_ALL, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) LOG(LOG4C_TRACE, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(LOG4C_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG(LOG4C_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG(LOG4C_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(LOG4C_ERROR, fmt, ##__VA_ARGS__)

#endif
