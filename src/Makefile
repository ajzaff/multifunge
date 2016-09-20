.PHONY: all
all: clean mf debug
dir:
	mkdir -p bin
mf: mf98 mf93
mf98: dir
	gcc -Wall -std=c99 -g -D__MF_98 multifunge.c -o bin/mf98
mf93: dir
	gcc -Wall -std=c99 -g -D__MF_93 multifunge.c -o bin/mf93
debug: debug98 debug93
debug98: dir
	gcc -Wall -std=c99 -g -DDEBUG -D__MF_98 multifunge.c -o bin/mf98dbg
debug93: dir
	gcc -Wall -std=c99 -g -DDEBUG -D__MF_93 multifunge.c -o bin/mf93dbg
clean:
	rm -rf bin
