#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

struct book_t {
  char *title;
  char *url;
  char *authors;
  char *year;
  char *publisher;
  char *pages;
  char *lang;
  char *size;
  char *ext;
  char *isbn;
  char *series;
};

void book_t_print(const struct book_t *book);
void book_t_free(const struct book_t *book);
void array_book_t_free(struct book_t **ptr, const int size);

#endif
