CFLAGS= -Wall

default: renbits.c
	gcc $(CFLAGS) renbits.c -o renbits

run: default
	./renbits

clean:
	rm renbits