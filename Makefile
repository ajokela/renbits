CFLAGS= -Wall

default: test.c
	gcc $(CFLAGS) test.c -o test

run: default
	./test

clean:
	rm test