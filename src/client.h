#ifndef CLIENT_H
#define CLIENT_H

#include "error.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum {
  NO_CONTENT_LENGTH = -1,
  BUFFER_SIZE = 1024,
};

int parse_http_header(int sock, ...);
char *page_downloader(const char *hostname, const char *path,
                      const char *filename);

#endif
