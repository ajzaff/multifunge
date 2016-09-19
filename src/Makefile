all:
	mkdir -p bin
	gcc -Wall -std=c99 -g multifunge.c -o bin/mf
clean:
	rm -rf bin
check:
	valgrind ./bin/mf ../examples/helloworld.funge --track-origins=yes --leak-check=full
