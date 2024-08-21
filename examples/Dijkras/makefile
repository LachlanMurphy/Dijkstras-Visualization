CC     = gcc
CFLAGS = -Wall -lglut -lGL -g
DEPS   = ../../src/lgraph.h
LIBS   = -lm

build:
	$(CC) -o run $(DEPS) main.c graph.c LL.c PQ.c ../../src/lgraph.c tree.c $(CFLAGS) $(LIBS)

