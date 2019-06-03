#ifndef TYPES_H
#define TYPES_H

#include "config.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FOR_BITSET(bs, c)                                                      \
  for (uint64_t c = 0, _bs = bs; _bs;                                          \
       _bs ^= (1ULL << c), c = log(LSONE(_bs)) / log(2))

/*
 * least significant one bit of an integer
 * relevant to iterate through bitset
 */
#define LSONE(i) (i & (-i))

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
  char *id;
  char *volume;
  char *edition;
  char *isbn;
  char *series;
  char *description;
  char *download_url;
  char *path;
  char *periodical;
};

typedef struct {
  struct book_t *books;
  int size;
} BOOK_CONTAINER;

struct pages {
  BOOK_CONTAINER lib[64];
  uint64_t bitset;
  int max_pages;
};

void book_t_print(const struct book_t *book);
void book_t_free(const struct book_t *book);
void array_book_t_free(BOOK_CONTAINER *book_arr);
void pages_book_t_free(struct pages *lib);

#endif

