BIN = main
OBJECTS = fonction.o main.o
CC = gcc
RM = rm -f
CFLAGS = -Wall -ansi -pedantic -std=c90

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) -Wall -pedantic
	
fonction.o : fonction.c fonction.h
	$(CC) -g -c fonction.c -o fonction.o $(CFLAGS)
	
main.o : main.c fonction.h
	$(CC) -g -c main.c -o main.o $(CFLAGS)
	
clean :
	$(RM) $(OBJECTS) $(BIN)
