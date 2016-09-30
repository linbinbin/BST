CC=gcc
CXX=g++
CFLAGS=-g -Wall -std=c99
CXXFLAGS=$(CFLAGS)
PROGS=test_tree
OBJS = tree.o
$(OBJS) : Makefile

all:$(PROGS)

.c.o:
	$(CC) -c -std=c99 $<

$(PROGS): $(OBJS) test_tree.o
	$(CC) -g -o $@ $^

.PHONY: clean
clean:
	RM $(PROGS) a.out *.o
