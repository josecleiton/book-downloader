#ifndef PARSE_H
#define PARSE_H

#include "error.h"
#include "types.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PARSE GEN LIB RUS EC HTML PAGES */

enum {
  AUTHORS,
  TITLE,
  PUBLISHER,
  YEAR,
  PAGES,
  LANG,
  SIZE,
  EXT,
  ISBN,
  SERIES,
  BUFFER_SIZE = 51200
};

/* return all books in the page */
char *search_page(const char *filename, struct book_t **book_array,
                  int *book_array_len);
/* return: download link of selected book */
char *book_page(const char *filename, struct book_t *selected_book,
                char **download_url, char **description);

FILE *open_file(const char *filename);
void format_file(FILE *stream, register char *buffer);
void handle_td_element(const char *buffer, const int buffer_len,
                       struct book_t *book, const int which_td);

#endif
