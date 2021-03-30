
CC=g++
CFLAGS=-I. -Wall -Wextra -pendantic
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
TARGETS  = main

all: $(TARGETS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o classes.o $(HEADERS)
	$(CC) main.o classes.o -o GameOfLife

clean:
	rm -f $(OBJECTS) $(TARGETS)
