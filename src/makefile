#I have no idea what I'm doing, Humina 2016
CC=g++
CFLAGS= -c -std=c++11
OFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES=DC.cpp Game.cpp hero.cpp Gamemanager.cpp HUD.cpp monster.cpp item.cpp reader.cpp combat.cpp
OBJECTS=$(SOURCES:.cpp=.o)
NAME = main

all: main

main: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(OFLAGS)
	rm $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

