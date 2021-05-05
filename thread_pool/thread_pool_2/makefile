src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CC = g++
CFLAGS = -Wall -g -lpthread

all:$(targets)

$(targets):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) test ps.out temp

