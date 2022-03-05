BIN = main
OBJECTS = api.o main.o
CC = gcc
RM = rm -f
CFLAGS = -Wall -ansi -pedantic -std=c90

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN) -Wall -pedantic
	
api.o : api.c api.h
	$(CC) -g -c api.c -o api.o $(CFLAGS)
	
main.o : main.c api.h
	$(CC) -g -c main.c -o main.o $(CFLAGS)
	
clean :
	$(RM) $(OBJECTS) $(BIN)
