OBJS = minimax.o connectfour.o
CC = g++
DEBUG = -g
CPPFLAGS = -std=c++11 -Wall -c $(DEBUG) 
LFLAGS = -Wall $(DEBUG)

GAMES_DIR=src/games

game : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o game

connectfour.o : $(GAMES_DIR)/connectfour.h  $(GAMES_DIR)/connectfour.cpp
	$(CC) $(CPPFLAGS) $(GAMES_DIR)/connectfour.cpp

minimax.o : src/minimax.h src/minimax.cpp 
	g++ $(CPPFLAGS) src/minimax.cpp

clean:
	rm *.o connect-four