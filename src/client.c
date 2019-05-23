#include "client.h"

int parse_http_header(int sock, ...) {
  char buff[BUFFER_SIZE] = "", *buffer_cursor = buff + 4;
  int bytes_received;
  while ((bytes_received = recv(sock, buffer_cursor, 1, 0))) {
    if (bytes_received == -1) {
      exit_and_report();
    }
    if ((buffer_cursor[-3] == '\r') && (buffer_cursor[-2] == '\n') &&
        (buffer_cursor[-1] == '\r') && (*buffer_cursor == '\n'))
      break;
    buffer_cursor += 1;
  }
  *buffer_cursor = '\0';
  buffer_cursor = buff + 4;
  puts(buffer_cursor);
  if (bytes_received) {
    if ((buffer_cursor = strstr(buffer_cursor, "Content-Length:"))) {
      sscanf(buffer_cursor, "%*s %d", &bytes_received);
    } else {
      bytes_received = NO_CONTENT_LENGTH;
    }
    if ((buffer_cursor =
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
                      const char *filename) {
  char buffer[BUFSIZ];
  char request[BUFFER_SIZE];
  char request_template[] = "GET /%s HTTP/1.1 \r\nHost: %s\r\n\r\n";
  int socketfd;
  struct addrinfo hints, *servinfo, *p;
  int status, request_len;
  int bytes_received;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(hostname, "http", &hints, &servinfo)) != 0) {
    perror("getaddrinfo");
    perror(gai_strerror(status));
    return error_msg("[ERROR] client.c - getaddrinfo");
  }

  /* search by valid socket */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((socketfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                           servinfo->ai_protocol)) == -1) {
      continue;
    }
    if (connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
      close(socketfd);
      continue;
    }
    break;
  }
  if (p == NULL) {
    perror("connect and socket");
    return error_msg("[ERROR] client.c - failed to connect");
  }
  request_len =
      snprintf(request, BUFFER_SIZE, request_template, path, hostname);
  fprintf(stderr, "Request = %s", request);
  if (send(socketfd, request, BUFFER_SIZE, 0) == -1) {
    perror("send");
    return error_msg("[ERROR] client.c - send failed");
  }
  int content_length;
  if (*filename) {
    content_length = parse_http_header(socketfd);
  } else {
    content_length = parse_http_header(socketfd, filename);
  }
  int bytes = 0;
  FILE *rcv_file = fopen(filename, "wb");
  if (rcv_file == NULL) {
    return error_msg("[ERROR] client.c - failed to open file");
  }
  /* receive bytes from server and output it in rcv_file stream */
  while ((bytes_received = recv(socketfd, buffer, BUFSIZ, 0))) {
    if (bytes_received == -1) {
      perror("recv");
      return error_msg("[ERROR] client.c - failed on recv function");
    }
    fwrite(buffer, sizeof(char), bytes_received, rcv_file);
    bytes += bytes_received;
    if (content_length != NO_CONTENT_LENGTH && bytes >= content_length)
      break;
  }
  /* free in sncbd.c */
  char *log_msg = (char *)malloc(48 * sizeof(char));
  snprintf(log_msg + 1, LOGMSG_SIZE - 1, "Finished! %.2lf KBs transfered.\n",
           bytes / (float)1024);
  *log_msg = '\0';

  /* post rotines */
  freeaddrinfo(servinfo);
  close(socketfd);
  fclose(rcv_file);
  return log_msg;
}

