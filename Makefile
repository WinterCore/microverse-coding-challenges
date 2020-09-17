FILES=$(wildcard src/*.c)
EXE=$(patsubst src/%.c, bin/%, $(FILES))

.PHONY: all
all: $(EXE)

bin/%: src/%.c
	gcc -Wall -ggdb -lm -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(EXE)
