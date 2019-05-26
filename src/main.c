#include "libsl/arg.h"
#include "scbd.h"
#include <stdarg.h>
#include <stdio.h>

char *argv0 = NULL;

int main(int argc, char *argv[]) {
  int arg_status = 0;
  char *args[ARG_LEN];
  memset(args, 0, ARG_LEN * sizeof(char*));
  if (argc == 1) {
    usage();
  }
  ARGBEGIN {
  case 'b':
    args[1] = ARGF();
    arg_status |= 1;
    break;
  case 'd':
    args[2] = ARGF();
    arg_status |= 2;
    break;
  case 's':
    args[0] = ARGF();
    break;
  case 'v':
    verbose = true;
    break;
  case 'h':
    help_message();
  default:
    usage();
  }
  ARGEND;
  return exec(args, arg_status);
}

