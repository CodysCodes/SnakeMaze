CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o fileread.o terminal.o game.o
EXEC = maze

ifdef DARK
CFLAGS += -D DARK
DARK : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c fileread.h terminal.h
	$(CC) -c main.c $(CFLAGS)

fileread.o : fileread.c 
	$(CC) -c fileread.c $(CFLAGS)

terminal.o : terminal.c 
	$(CC) -c terminal.c $(CFLAGS)

game.o : game.c
	$(CC) -c game.c $(CFLAGS)

clean : 
	rm -f $(EXEC) $(OBJ)