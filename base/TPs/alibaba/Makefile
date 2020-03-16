CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

ifeq ($(TESTS), 1)
CFLAGS += -DTESTS
endif

all: alibaba

.PHONY: clean
clean:
	-DEL *.o