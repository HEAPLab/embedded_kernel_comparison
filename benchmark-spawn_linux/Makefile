CFLAGS ?= -O2 -g
CC := arm-linux-gcc
CXX := arm-linux-g++

.PHONY: all
all: benchmark-spawn child

benchmark-spawn: benchmark-spawn.cpp benchmark.h
	$(CXX) $(CFLAGS) -o $@ $<

child: child.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f benchmark-spawn child *.gdb
