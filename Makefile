CC     := gcc
CFLAGS := -Wall -g
TARGET := bin/main

SRCS := $(wildcard src/*.c)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst src/%.c,bin/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean
