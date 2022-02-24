CC = gcc
CFLAGS  = -O2 -g -Wall -Wextra -Werror $(IFLAGS)
LDFLAGS = -pthread -lpthread

EXECS   = heavy standard setup

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(EXECS)

heavy: heavy.o random.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

standard: standard.o random.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(EXECS)  *.o
