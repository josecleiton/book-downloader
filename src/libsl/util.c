/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		die("calloc:");
	return p;
}

void *
erealloc(void *p, size_t size)
{
	if (!(p = realloc(p, size)))
		die("realloc:");

	return p;
}

FILE*
efopen(const char *restrict filename, const char *restrict mode ) {
	FILE* f;
	if(!(f = fopen(filename, mode))) {
		die("fopen:");
	}
	return f;
}

void
die(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(1);
}
