#ifndef ERROR_H
#define ERROR_H

#include "libsl/arg.h"
#include "libsl/util.h"
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE -1
#define SUCCESS 0

#define strcenter(str, col, len)                                               \
  ((int)(col + len / 2)), str, ((int)(col - len / 2)), ""
#define strcenter_len(str, col) strcenter(str, col, strlen(str))
#define printf_center(str, col)                                                \
  printf("%*s%*s", strcenter(str, col, strlen(str)))
#define printf_int_center(num, col)                                            \
  {                                                                            \
    char tmp_integer[10];                                                      \
    sprintf(tmp_integer, "%d", num);                                           \
    printf_center(tmp_integer, col);                                           \
  }

enum { LOGMSG_SIZE = 128 };

extern bool verbose;

char *error_msg(const char *msg);
void usage(void);

#endif

