#I have no idea what I'm doing, Humina 2016
CC=g++
CFLAGS= -c -std=c++11
OFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
NAME = main

all: main

main: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(OFLAGS)
	rm $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

