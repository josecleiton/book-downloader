CC = gcc
CFLAGS = -g -Wall -Wextra -Wcast-align -lm
SRCS = client.c  error.c  main.c  parse.c  types.c  scbd.c  libsl/util.c
OBJS = $(SRCS:.c=.o)
MAIN = scbd

all: $(MAIN)
	   @echo Simple C Book Downloader has been compiled

$(MAIN): $(OBJS)
	       $(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) *.o *~ $(MAIN)
