CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: perf

.PHONY: clean
clean:
	rm -f *~ *.o perf

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
