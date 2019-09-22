CC=gcc
CFLAGS  = -g -Wall

default: prog

get-deps:
	# Assuming Debian or Ubuntu here
	sudo apt-get install -y build-essential check

dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c dictionary.h

spell.o: spell.c
	$(CC) $(CFLAGS) -c spell.c

test.o: test_main.c
	$(CC) $(CFLAGS) -c test_main.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

test: dictionary.o spell.o test_main.o
	$(CC) $(CFLAGS) -o test_main test_main.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main

prog: dictionary.o spell.o main.o
	$(CC) $(CFLAGS) -o spell_check dictionary.o spell.o main.o

clean:
	rm dictionary.o spell.o main.o test_main.o

cleanall:clean
	rm spell_check dictionary.h.gch
