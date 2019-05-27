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

enum { LOGMSG_SIZE = 128 };

extern bool verbose;

char *error_msg(const char *msg);
void usage(void);

#endif

