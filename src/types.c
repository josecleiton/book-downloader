#include "types.h"

void bookt_t_print(struct book_t* book) {
   printf("TITLE = %s\nURL = %s\nAUTHORS = %s\nYEAR = %s\nPUBLISHER = %s\nLANG = %s\nSIZE = %s\nEXT = %s\n\n",
         book->title, book->url, book->authors, book->year,
         book->publisher, book->lang, book->size, book->ext);
}

/* kai */
void book_t_free(const struct book_t* book) {
   free(book->title);
   free(book->url);
   free(book->authors);
   free(book->year);
   free(book->publisher);
   free(book->pages);
   free(book->lang);
   free(book->size);
   free(book->ext);
   if(book->isbn) {
      free(book->isbn);
   }
   if(book->series) {
      free(book->series);
   }
}

void array_book_t_free(struct book_t** ptr_to_array, const int size) {
   struct book_t* arr = *ptr_to_array;
   for(int i=0; i < size; i += 1) {
      book_t_free(&arr[i]);
   }
   free(*ptr_to_array);
   *ptr_to_array = NULL;
}
