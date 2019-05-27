.POSIX:
CC = gcc
CFLAGS = -g -Wall -Wextra -Wcast-align -lm
SRCS = client.c  error.c  main.c  parse.c  types.c  scbd.c  libsl/util.c
OBJS = $(SRCS:.c=.o)
MAIN = scbd

all: $(MAIN)
	   @echo Simple C Book Downloader has been compiled

$(MAIN): $(OBJS)
	       $(CC) $(CFLAGS) -o $(MAIN) $(OBJS)
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
				 @echo Please take a look in README and LICENSE files.
				 @echo Have a nice day

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(MAIN)

.PHONY: all clean install uninstall
