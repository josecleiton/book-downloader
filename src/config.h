#ifndef CONFIG_H
#define CONFIG_H
/*
 *
 * USER CONFIGURATION FILE
 * Read the repository doc for more info.
 *
 */

/* where the books will stay */
static const char save_dir[] = "~/.cache/scbd";

/* where the .bib will stay */
static const char save_ref_dir[] = "~/.cache/scbd";

/* library genesis address */
static const char gen_lib[] = "gen.lib.rus.ec";

/* path to download from previous hostname */
static const char gen_lib_search_path[] = "search.php?req=";

/* 25 | 50 | 100 */
static const int MAX_BOOKS_PER_PAGE = 25;

/* id | author | title | publisher | year | pages
 * filesize | extension*/
static const char sort_book_order[] = "year";

/* ASC | DESC */
static const char sort_mode[] = "DESC";

#endif

