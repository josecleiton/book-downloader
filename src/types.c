#include "types.h"

void bookt_t_print(struct book_t *book) {
  printf("TITLE = %s\nURL = %s\nAUTHORS = %s\nYEAR = %s\nPUBLISHER = %s\nLANG "
         "= %s\nSIZE = %s\nEXT = %s\n\n",
         book->title, book->url, book->authors, book->year, book->publisher,
         book->lang, book->size, book->ext);
}

/* kai */
void book_t_free(const struct book_t *book) {
  free(book->title);
  free(book->url);
  free(book->authors);
  free(book->year);
  free(book->publisher);
  free(book->pages);
  free(book->lang);
  free(book->size);
  free(book->ext);
  if (book->edition) {
    free(book->edition);
  }
  if (book->id) {
    free(book->id);
  }
  if (book->isbn) {
    free(book->isbn);
  }
  if (book->series) {
    free(book->series);
  }
  if (book->volume) {
    free(book->volume);
  }
  if (book->description) {
    free(book->description);
  }
  if (book->download_url) {
    free(book->download_url);
  }
  if (book->path) {
    free(book->path);
  }
}

void array_book_t_free(BOOK_CONTAINER *book_arr) {
  for (int i = 0; i < book_arr->size; i += 1) {
    book_t_free(&book_arr->books[i]);
  }
  free(book_arr->books);
}

void pages_book_t_free(struct pages *lib) {
  FOR_BITSET(lib->bitset, cursor) { array_book_t_free(&lib->lib[cursor]); }
}

