#include <stdio.h>
#include <stdarg.h>
#include "scbd.h"
#include "libsl/arg.h"

char* argv0 = NULL;

int main(int argc, char* argv[]) {
   char args[3][LOGMSG_SIZE * 2];
   // memset(args, 0, ARG_LEN * sizeof(char*));
   if(argc == 1) {
      usage();
   }
   ARGBEGIN {
      case 'b':
         strcpy(args[1], ARGF());
         break;
      case 'd':
         strcpy(args[2], ARGF());
         break;
      case 's':
         strcpy(args[0], ARGF());
         break;
      default:
         help_message();
         usage();
   } ARGEND;
   return render_and_exec(args);
}
