#include "libsl/arg.h"
#include "scbd.h"
#include <stdarg.h>
#include <stdio.h>

char *argv0 = NULL;

int main(int argc, char *argv[]) {
  int arg_status = 0;
  char args[3][LOGMSG_SIZE * 2];
  memset(args, 0, 3 * LOGMSG_SIZE * 2 * sizeof(char));
  if (argc == 1) {
    usage();
  }
  ARGBEGIN {
  case 'b':
    strcpy(args[1], ARGF());
    arg_status |= 1;
    break;
  case 'd':
    strcpy(args[2], ARGF());
    arg_status |= 2;
    break;
  case 's':
    strcpy(args[0], ARGF());
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
  return render_and_exec(args, arg_status);
}

