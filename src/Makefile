.PHONY: all
all: clean dir prod debug
dir:
	mkdir -p bin
prod: dir
	gcc -Wall -std=c99 -g multifunge.c -o bin/mf
debug: dir
	gcc -Wall -std=c99 -g -DDEBUG multifunge.c -o bin/mfdbg
clean:
	rm -rf bin
