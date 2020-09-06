EXE=bin/main bin/wtf

.PHONY: all
all: $(EXE)

bin/%: src/%.c
	gcc -Wall -ggdb -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(EXE)
