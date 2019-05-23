#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE EXIT_FAILURE

enum { LOGMSG_SIZE = 128 };

char* error_msg(const char* msg);
void exit_and_report(void);

#endif
