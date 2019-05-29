#include "client.h"

int parse_http_header(int sock, ...) {
  char buff[CLIENT_BUFFER_SIZE] = "", *buffer_cursor = buff + 4;
  int bytes_received;
  while ((bytes_received = recv(sock, buffer_cursor, 1, 0))) {
    if (bytes_received == -1)
      die("client.c - parse_http_header:");
    if ((buffer_cursor[-3] == '\r') && (buffer_cursor[-2] == '\n') &&
        (buffer_cursor[-1] == '\r') && (*buffer_cursor == '\n'))
      break;
    buffer_cursor += 1;
  }
  *buffer_cursor = '\0';
  buffer_cursor = buff + 4;
  /* puts(buffer_cursor); */
  if (bytes_received) {
    if ((buffer_cursor = strstr(buffer_cursor, "Content-Length:")))
      sscanf(buffer_cursor, "%*s %d", &bytes_received);
    else
      bytes_received = NO_CONTENT_LENGTH;
    if (buffer_cursor &&
        (buffer_cursor =
             strstr(buffer_cursor, "Content-Disposition: attachment"))) {
      /* http header of book file */
      va_list arg_list;
      va_start(arg_list, sock);
      char *book_filename = va_arg(arg_list, char *);
      sscanf(buffer_cursor,
             "Content-Disposition: attachment; filename=\"%[^\"]",
             book_filename);
      va_end(arg_list);
    }
  }
  return bytes_received;
}

char *page_downloader(const char *hostname, const char *path,
                      const int file_status, FILE **rcv_file,
                      const int show_progress_bar, ...) {
  char buffer[BUFSIZ];
  char request[CLIENT_BUFFER_SIZE] = {'\0'};
  char request_template[] = "GET /%s HTTP/1.1 \r\nHost: %s\r\n\r\n";
  char filename[255];
  char *log_msg;
  int socketfd;
  struct addrinfo hints, *servinfo, *p;
  int status;
  int bytes_received;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(hostname, "http", &hints, &servinfo))) {
    perror("getaddrinfo");
    perror(gai_strerror(status));
    return error_msg("[ERROR] client.c - getaddrinfo");
  }

  /* search by valid socket */
  for (p = servinfo; p; p = p->ai_next) {
    if ((socketfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                           servinfo->ai_protocol)) == -1)
      continue;
    if (connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
      close(socketfd);
      continue;
    }
    break;
  }
  if (!p) {
    perror("connect and socket");
    return error_msg("[ERROR] client.c - failed to connect");
  }

  snprintf(request, CLIENT_BUFFER_SIZE, request_template, path, hostname);
  if (verbose)
    fprintf(stderr, "Request = %s", request);
  if (send(socketfd, request, CLIENT_BUFFER_SIZE, 0) == -1) {
    perror("send");
    return error_msg("[ERROR] client.c - send failed");
  }
  int content_length;
  if (file_status == TMP_FILE) {
    content_length = parse_http_header(socketfd);
    *rcv_file = tmpfile();
  } else {
    content_length = parse_http_header(socketfd, filename);
    va_list arg_list;
    va_start(arg_list, show_progress_bar);
    char **book_filename = va_arg(arg_list, char **);
    const long book_fn_len = va_arg(arg_list, const size_t);
    const long catched_fn_len = strlen(filename);
    *book_filename = erealloc(
        *book_filename, (book_fn_len + catched_fn_len + 2) * sizeof(char));
    if (file_status == JUST_FILENAME)
      **book_filename = '\0';
    strcat(*book_filename, filename);
    va_end(arg_list);
    if (file_status == JUST_FILENAME) {
      log_msg = (char *)ecalloc(1, sizeof(char));
      goto POST_ROTINES;
    }
    putchar('\n');
    *rcv_file = efopen(*book_filename, "wb+");
  }
  if (!(*rcv_file))
    return error_msg("[ERROR] client.c - failed to open file");
  int bytes = 0;
  /* receive bytes from server and output it in rcv_file stream */
  while ((bytes_received = recv(socketfd, buffer, BUFSIZ, 0))) {
    if (bytes_received == -1) {
      perror("recv");
      return error_msg("[ERROR] client.c - failed on recv function");
    }
    fwrite(buffer, sizeof(char), bytes_received, *rcv_file);
    bytes += bytes_received;
    if (content_length != NO_CONTENT_LENGTH &&
        ((show_progress_bar && progress_bar(bytes, content_length)) ||
         (bytes >= content_length)))
      break;
  }
  if (verbose)
    fprintf(stderr, "Bytes received = %d\n", bytes);
  fflush(*rcv_file);
  log_msg = (char *)ecalloc(LOGMSG_SIZE, sizeof(char));
  snprintf(log_msg + 1, LOGMSG_SIZE - 1, "Finished! %.2lf KBs transfered.",
           bytes / (float)1024);

POST_ROTINES:
  freeaddrinfo(servinfo);
  close(socketfd);
  return log_msg;
}

bool progress_bar(const int curr_val, const int total) {
  int cli_ratio = (curr_val * PROG_BAR_LEN) / total,
      real_ratio = (curr_val * 100) / total;
  printf(" [");
  for (int i = 0; i < cli_ratio; i += 1)
    putchar('-');
  for (; cli_ratio < PROG_BAR_LEN; cli_ratio += 1)
    putchar(' ');
  printf("] %d%c\r", real_ratio, '%');
  fflush(stdout);
  return real_ratio >= 100;
}

