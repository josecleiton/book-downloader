#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include "libsl/arg.h"
#include "libsl/util.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE -1
#define SUCCESS EXIT_SUCCESS

enum { LOGMSG_SIZE = 128 };

char *error_msg(const char *msg);
void exit_and_report(void);
void usage(void);

#endif
