#ifndef SCBD_H
#define SCBD_H

#include "client.h"
#include "config.h"
#include "error.h"
#include "parse.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if __unix__
#define CLEAR system("clear")
#define HOMEPATH "HOME"
#elif __WIN32 || __WIN64
#define CLEAR system("cls")
#define HOMEPATH "HOMEPATH"
#endif

#define CONST_ARR_LEN(a) (sizeof(a) / sizeof(*a))
#define strcenter(str, col, len)                                               \
  ((int)(col + len / 2)), str, ((int)(col - len / 2)), ""
#define strcenter_len(str, col) strcenter(str, col, strlen(str))
#define printf_center(str, col)                                                \
  printf("%*s%*s", strcenter(str, col, strlen(str)))
#define printf_int_center(num, col)                                            \
  {                                                                            \
    char tmp_integer[10];                                                      \
    sprintf(tmp_integer, "%d", num);                                           \
    printf_center(tmp_integer, col);                                           \
  }

/*
 * Simple C Book Downloader
 * from http://gen.lib.rus.ec
 * check the LICENSE file
 */

enum {
  SEARCH_PATTERN,
  BOOK_BIB_PATH,
  BOOK_PATH,
  SORT_ORDER,
  SORT_MODE,
  ARG_LEN = 5,
};

int exec(char *args[]);
int download_search_page(char *pattern, char **log_msg, struct book_t **books,
                         int *books_len, const int curr_page,
                         uint64_t *cached_pages, const char *sort_book_order,
                         const char *sort_mode);
void download_mirror_page(struct book_t *selected_book, char **log_msg);
bool download_book_page(struct book_t *selected_book, char **log_msg);
char *download_book(struct book_t *selected_book, char *local_save_ref_dir,
                    char *local_save_dir) ;
void generate_ref(const struct book_t *selected_book, const long start_book_fn,
                  char *local_save_ref_dir);

uint64_t is_cached(const int curr_page, const uint64_t cached_pages);
void print_cached_pages(const uint64_t bitset);
void split_url(const char *url, char **hostname, char **path);

void logo(void);
void greeting_message(void);
void help_message(void);
void success_message(char *msg, const struct book_t *selected_book,
                     const char *local_save_ref_dir);
void print_table_of_books(struct book_t *array, const int array_len,
                          const int curr_page, const int status);
void draw_book_column(char *text, const size_t len);
void print_more_info(struct book_t *selected_book);
void check_log_msg(char *msg);
char *get_dir(char *dir, long *len);

int user_input(const char *msg, const char *info, int (*check_input)(char *in));
int user_input_arg(const char *msg, const char *info, char *container);
int check_input_search_page(char *in);
int check_input_book(char *in);

#endif
