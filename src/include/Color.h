#ifndef COLOR_H
#define COLOR_H

typedef struct
{
  const char *const fg;
  const char *const bg;
} Color;

// http://ascii-table.com/ansi-escape-sequences.php
// http://xahlee.info/comp/cars_trains_airplanes_boats.html

const Color BLACK = {"\033[0;30m", "\033[0;40m"};
const Color RED = {"\033[0;31m", "\033[0;41m"};
const Color GREEN = {"\033[0;32m", "\033[0;42m"};
const Color YELLOW = {"\033[0;33m", "\033[0;43m"};
const Color BLUE = {"\033[0;34m", "\033[0;44m"};
const Color MAGENTA = {"\033[0;35m", "\033[0;45m"};
const Color CYAN = {"\033[0;36m", "\033[0;46m"};
const Color WHITE = {"\033[0;37m", "\033[0;47m"};

const Color RESET = {"\033[0m", "\033[0m"};

const Color BOLD = {"\e[1m", "\e[0m"};

#endif
