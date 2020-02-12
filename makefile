CC=gcc
CFLAGS=-Wall
SRC=puissance4.c main.c
OBJ=$(SRC:.c=.o)

puissance4 : $(OBJ) puissance4.h
	$(CC) -o $@ $(OBJ)

%.o : %.c
	$(CC) -c $< $(CFLAGS)

clean :
	rm *.o *~core
