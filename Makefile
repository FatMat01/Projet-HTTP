BIN = main
OBJECTS = parseur.o main.o
CC = gcc
RM = rm -f
CFLAGS = -Wall -ansi -pedantic -std=c90

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) -Wall -pedantic
	
parseur.o : parseur.c parseur.h
	$(CC) -g -c parseur.c -o parseur.o $(CFLAGS)
	
main.o : main.c parseur.h
	$(CC) -g -c main.c -o main.o $(CFLAGS)
	
clean :
	$(RM) $(OBJECTS) $(BIN)
