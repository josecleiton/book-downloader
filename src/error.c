#include "error.h"

bool verbose = false;

char *error_msg(const char *msg) {
  size_t result_size = 128 + strlen(msg);
  char *result = (char *)ecalloc(result_size, sizeof(char));
  *result = '\0';
  sprintf(result, "%s\n%s", msg, strerror(errno));
  return result;
}

void usage(void) { die("usage: -s STR [ -b STR ] [ -d STR ] [ -o STR ] [ -m ASC | DESC ] [ -v ]"); }

