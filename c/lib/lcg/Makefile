all: lcg.o test

lcg.o: lcg.c lcg.h
	$(CC) -o $@ -flto -O3 -c lcg.c

test: test.c lcg.o lcg.h
	$(CC) -o $@ -flto -O3 test.c lcg.o -lm

PHONY: all
