CC= gcc
CFLAGS=-Wall -ggdb

all: main test

main: main.o linked-list.o
	$(CC) $(CFLAGS) -o output main.o linked-list.o

test: test.o linked-list.o
	$(CC) $(CFLAGS) -o test test.o linked-list.o

test.o: test.c ../minunit.h
	$(CC) $(CFLAGS) -c test.c -o test.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

linked-list.o: linked-list.c linked-list.h
	$(CC) $(CFLAGS) -c linked-list.c -o linked-list.o

clean:
	rm -rfv *.o output test
