CC = gcc
LD = gcc
CFLAGS = -std=c99 -Wall -Wextra -g3 -O2 -Werror -Wshadow -Wconversion -Wdouble-promotion -Wformat=2 -Wformat-truncation=2 -Wundef -fno-common -fstack-usage -Wfloat-equal -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -ffunction-sections -fdata-sections -Iinclude/ -fPIC
LDFLAGS = -Wl,--gc-sections -Wl,--print-gc-sections

all: lib/libdirectory.so build-tests

lib/libdirectory.so: obj/directory.o obj/contact.o obj/hash.o obj/utils.o
	$(CC) -shared $^ -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build-tests:
	make -C tests/

.PHONY: clean

clean:
	rm -rf obj/*.o obj/*.su lib/libdirectory.so
	make -C tests/ clean
