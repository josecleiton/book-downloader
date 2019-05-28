#include "libsl/arg.h"
#include "scbd.h"
#include <stdarg.h>
#include <stdio.h>

char *argv0;

int main(int argc, char *argv[]) {
  char *args[ARG_LEN];
  memset(args, 0, ARG_LEN * sizeof(char*));
  ARGBEGIN {
  case 'b':
    args[1] = ARGF();
    break;
  case 'd':
    args[2] = ARGF();
    break;
  case 's':
    args[0] = ARGF();
    break;
  case 'm':
    args[4] = ARGF();
    break;
  case 'o':
    args[3] = ARGF();
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
  return exec(args);
}

