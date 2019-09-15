CC=gcc
CFLAGS  = -g -Wall

default: prog

dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c dictionary.h

spell.o: spell.c
	$(CC) $(CFLAGS) -c spell.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

prog: dictionary.o spell.o main.o
	$(CC) $(CFLAGS) -o spell_check dictionary.o spell.o main.o

clean:
	$(RM) count *.o *~

cleanall:clean
	rm spell_check
