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
  BOOK_AUTHORS = 1,
  BOOK_TITLE,
  BOOK_PUBLISHER,
  BOOK_YEAR,
  BOOK_PAGES,
  BOOK_LANG,
  BOOK_SIZE,
  BOOK_EXT,
  BOOK_ISBN,
  BOOK_SERIES,
  BOOK_PARSE_BUFFER_SIZE = 65536
};

/* return all books in the page */
char *search_page(FILE *page_file, struct book_t **book_array,
                  int *book_array_len, int *status, int *max_pages_in_search);
/* return: download link of selected book */
char *book_page(FILE *page_file, struct book_t *selected_book);
char *mirror_page(FILE *page_file, struct book_t *selected_book);

void format_file(FILE *stream, register char *buffer);
int handle_td_element(const char *buffer, const int buffer_len,
                      struct book_t *book, const int which_td);
int get_max_pages(const char *buffer);

#endif

