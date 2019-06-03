#ifndef CLIENT_H
#define CLIENT_H

#include "error.h"

#if __unix__
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#elif __WIN32 || __WIN64
#include <windows.h>
#include <ws2tcpip.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  NO_CONTENT_LENGTH = -1,
  REGULAR_FILE,
  TMP_FILE,
  JUST_FILENAME,
  PROGRESS_BAR,
  SEARCH_PAGE,
  MIRROR_PAGE,
  BOOK_PAGE,
  PROG_BAR_LEN = 70,
  CLIENT_BUFFER_SIZE = 1024,
};

int parse_http_header(int sock, ...);
char *page_downloader(const char *hostname, const char *path, FILE **rcv_file,
                      int *file_size, const int file_status,
                      const int show_progress_bar, ...);
bool progress_bar(const int curr_val, const int total);

#endif

