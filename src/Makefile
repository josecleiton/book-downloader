.POSIX:
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Wcast-align
SRCS = client.c  error.c  main.c  parse.c  types.c  scbd.c  libsl/util.c
OBJS = $(SRCS:.c=.o)
LIBS = -lm
MAIN = scbd
VERSION = 0.1
MANPREFIX = $(PREFIX)/share/man


all: $(MAIN)
	   @echo Simple C Book Downloader has been compiled

$(MAIN): $(OBJS)
	       $(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)
				 $(CLEAN)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) *.o *~ $(MAIN)

PREFIX = /usr/local

install: $(MAIN)
				 mkdir -p $(DESTDIR)$(PREFIX)/bin
				 cp -f $(MAIN) $(DESTDIR)$(PREFIX)/bin
				 chmod 755 $(DESTDIR)$(PREFIX)/bin/$(MAIN)
				 mkdir -p $(DESDIR)$(MANPREFIX)/man1
				 sed "s/VERSION/$(VERSION)/g" < $(MAIN).1 > $(DESTDIR)$(MANPREFIX)/man1/$(MAIN).1
				 chmod 644 $(DESDIR)$(MANPREFIX)/man1/$(MAIN).1
				 @echo Please take a look in README and LICENSE files.
				 @echo Have a nice day

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(MAIN)
	rm -f $(DESDIR)$(MANPREFIX)/man1/$(MAIN).1

.PHONY: all clean install uninstall
