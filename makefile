CC = g++
CFLAGS  = -g -Wall

all: util.o main.o
	$(CC) $(CFLAGS) -o grade_estimate util.o main.o
main.o: main.cpp util.h
	$(CC) $(CFLAGS) -c main.cpp
util.o: util.cpp util.h
	$(CC) $(CFLAGS) -c util.cpp
clean:
	rm grade_estimate *.o
