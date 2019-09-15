CC=gcc
CFLAGS  = -g -Wall

default: prog

dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c dictionary.h

spell.o: spell.c
	$(CC) $(CFLAGS) -c spell.c

<<<<<<< HEAD
prog: dictionary.o spell.o
	$(CC) $(CFLAGS) -o spell_check dictionary.o spell.o
=======
prog: dictionary.o spell.o
	$(CC) $(CFLAGS) -o spell_check dictionary.o spell.o
>>>>>>> 745eb01a6b124a7e792a2b12310500a7eff63114

clean:
	$(RM) count *.o *~

cleanall:clean
	rm spell_check
