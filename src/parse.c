#include "parse.h"

FILE *open_file(const char *filename) {
  FILE *stream;
  if ((stream = fopen(filename, "rb")) == NULL) {
    exit_and_report();
  }
  return stream;
}

void format_file(FILE *stream, register char *buffer) {
  /* take care of end of lines and multiple spaces in linear time */
  register char aux;
  register bool catched_space = false;
  while ((aux = fgetc(stream)) != EOF) {
    if ((!iscntrl(aux) && aux != ' ') || (aux == ' ' && !catched_space)) {
      *buffer = aux;
      buffer += 1;
      //   putchar(aux);
    }
    catched_space = aux == ' ';
  }
  fclose(stream);
}

void handle_td_element(const char *buffer, const int buffer_len,
                       struct book_t *book, const int which_td) {
  /* puts(buffer); */
  /* printf("%d\n\n", which_td); */

  register char *match = NULL;
  if (which_td == AUTHORS) {
    size_t authors_len = 0LL;
    int authors_count = 0;
    while ((match = strstr(buffer, "author"))) {
      if (authors_count) {
        book->authors[authors_len++] = ',';
        book->authors[authors_len++] = ' ';
      }
      match = strchr(match, '>') + 1;
      char *close_tag = strchr(match, '<');
      *close_tag = '\0';
      for (int i = 0; match[i]; i += 1, authors_len += 1) {
        book->authors[authors_len] = match[i];
      }
      buffer = close_tag + 1;
      authors_count += 1;
    }
    book->authors[authors_len] = '\0';
  } else if (which_td == TITLE) {
    /* search for the book's url and it's title */
    match = strstr(buffer, "book");
    char *close_tag = strchr(match, '\'');
    *close_tag = '\0';
    book->url = (char *)malloc((close_tag - match + 2) * sizeof(char));
    strcpy(book->url, match);
    /* puts(book->url); */

    match = strchr(close_tag + 1, '>') + 1;
    close_tag = strchr(match, '<');
    *close_tag = '\0';
    book->title = (char *)malloc((close_tag - match + 2) * sizeof(char));
    strcpy(book->title, match);
    /* puts(book->title); */

  } else if (which_td == YEAR) {
    /* just jump the nowrap parameter */
    match = strchr(buffer, '>') + 1;
    book->year = (char *)malloc(((match - buffer) - buffer_len) * sizeof(char));
    strcpy(book->year, match);
  } else if (which_td == PUBLISHER) {
    book->publisher = (char *)malloc(buffer_len * sizeof(char));
    strcpy(book->publisher, buffer);
  } else if (which_td == PAGES) {
    book->pages = (char *)malloc(buffer_len * sizeof(char));
    strcpy(book->pages, buffer);
  } else if (which_td == LANG) {
    book->lang = (char *)malloc(buffer_len * sizeof(char));
    strcpy(book->lang, buffer);
  } else if (which_td == SIZE) {
    match = strchr(buffer, '>') + 1;
    book->size = (char *)malloc(((match - buffer) - buffer_len) * sizeof(char));
    strcpy(book->size, match);
  } else {
    match = strchr(buffer, '>') + 1;
    book->ext = (char *)malloc(((match - buffer) - buffer_len) * sizeof(char));
    strcpy(book->ext, match);
  }
}

/*
 * GREP THE [2-9] TD AFTER FIRST TR
 * AUTHORS | TITLE | PUBLISHER | YEAR | PAGES | LANG | SIZE | EXT
 */
char *search_page(const char *filename, struct book_t **book_array,
                  int *book_array_len) {

  FILE *page_file = open_file(filename);
  enum {
    PATTERNS = 4,
    MAX_TD_PER_SEARCH = 8,
    BOOKS_PER_PAGE = 25,
    FILE_BEG = 40000, /* file beginning position */
  };

  /* all patterns we are looking for in html page */
  static char *pattern[] = {
      "<table width=100\% cellspacing=1 cellpadding=1 rules=rows class=c "
      "align=center><tr",
      "<tr valign=top bgcolor",
      "<td",
      "</td",
  };

  /* set the file's cursor and compute it's size */
  if (fseek(page_file, FILE_BEG, SEEK_SET) && ferror(page_file)) {
    exit_and_report();
  }
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
  if (buffer == NULL) {
    exit_and_report();
  }

  /* put the formated file in memory */
  format_file(page_file, buffer);
  page_file = NULL;

  struct book_t *books;
  /* the memory must be "released" in sncbd.c */
  books = *book_array =
      (struct book_t *)calloc(BOOKS_PER_PAGE, sizeof(struct book_t));
  if (*book_array == NULL) {
    exit_and_report();
  }
  /* UNNECESSARY constant down here */
  *book_array_len = BOOKS_PER_PAGE;

  char *match_cursor = NULL;
  int book_count = 0;

  /* jump after book's table and it's first tr in html buffer */
  char *buffer_cursor = strstr(buffer, pattern[0]) + 85;
  if (buffer_cursor == NULL) {
    /* http bad request */
    return error_msg("[ERROR] parse.c - HTTP");
  }

  while (book_count < BOOKS_PER_PAGE) {
    /* i is the pattern cursor and j is the td count */
    for (int i = 1, j = -1; i < PATTERNS; i += 1) {
      while (j < MAX_TD_PER_SEARCH) {
        if ((match_cursor = strstr(buffer_cursor, pattern[i]))) {
          if (i == 1) {
            /* ignore first td */
            match_cursor += 36;
            buffer_cursor = match_cursor;
            break;
          } else if (i == 2) {
            if (j == -1)
              j = 0;
            /* jump the td tag */
            match_cursor += 4;
            /* search for the td close tag */
            char *close_td = strstr(match_cursor, pattern[i + 1]);
            if (close_td == NULL) {
              return error_msg("[ERROR] parse.c - HTTP");
            }
            *close_td = '\0';
            handle_td_element(match_cursor, close_td - match_cursor + 1,
                              &books[book_count], j);

            match_cursor = buffer_cursor = close_td + 1;
            j += 1;
          }
        } else {
          return error_msg("[ERROR] parse.c - HTTP");
        }
      }
    }
    /*book_t_print(&books[book_count]); */
    /* scanf("%*c"); */
    book_count += 1;
  }

  /* must be "free" in snbd.c */
  char *log_msg = (char *)malloc(LOGMSG_SIZE * sizeof(char));
  if (log_msg == NULL) {
    exit_and_report();
  }

  strcpy(log_msg + 1, "Pick the book!\n");
  /* null in beginning as "return 0" */
  *log_msg = '\0';

  /* post rotines */
  free(buffer);
  return log_msg;
}

char *book_page(const char *filename, struct book_t *selected_book,
                char **download_url, char **description) {
  FILE *page_file = open_file(filename);
  enum {
    BOOK_DOWNLOAD_LINK,
    BOOK_SERIES,
    BOOK_ISBN,
    BOOK_DESCRIPTION,
    PATTERNS = 4,
  };

  char *buffer, *match, *buffer_cursor, *close_tag;
  /* all patterns we are looking for in html page */
  static char *pattern[] = {
      "<h2 style=\"text-align:center\">",
      "Series:",
      "ISBN:",
      "Description:",
  };

  match = buffer_cursor = buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
  if (buffer == NULL) {
    exit_and_report();
  }

  /* put the formated file in memory */
  format_file(page_file, buffer);
  page_file = NULL;

  for (int i = 0; i < PATTERNS; i++) {
    if ((match = strstr(buffer_cursor, pattern[i]))) {
      if (i == BOOK_DOWNLOAD_LINK) {
        match = strstr(match, "href") + 6;
        close_tag = strchr(match, '\"');
        *close_tag = '\0';
        *download_url = (char *)malloc((close_tag - match + 1) * sizeof(char));
        if (*download_url == NULL) {
          exit_and_report();
        }
        strcpy(*download_url, match);
      } else if (i == BOOK_SERIES) {
        match += 8;
        close_tag = strchr(match, '<');
        *close_tag = '\0';
        selected_book->series =
            (char *)malloc((close_tag - match + 1) * sizeof(char));
        strcpy(selected_book->series, match);
      } else if (i == BOOK_ISBN) {
        match += 6;
        close_tag = strchr(match, '<');
        *close_tag = '\0';
        selected_book->isbn =
            (char *)malloc((close_tag - match + 1) * sizeof(char));
        strcpy(selected_book->isbn, match);
      } else if (match) { /* may not have description */
        match = strchr(match, '>') + 1;
        close_tag = strchr(match, '<');
        /* must be "free" in snbd.c */
        *description = (char *)malloc((close_tag - match + 1) * sizeof(char));
        if (*description == NULL) {
          exit_and_report();
        }
        *close_tag = '\0';
        strcpy(*description, match);
      }
      buffer_cursor = close_tag + 1;
    } else {
      return error_msg("[ERROR] parse.c - HTTP REQUEST");
    }
  }

  /* must be "free" in snbd.c */
  char *log_msg = (char *)malloc(LOGMSG_SIZE * sizeof(char));
  if (log_msg == NULL) {
    exit_and_report();
  }

  strcpy(log_msg + 1, "Pick the book!\n");
  /* null in beginning as "return 0" */
  *log_msg = '\0';

  /* post rotines */
  free(buffer);
  return log_msg;
}
