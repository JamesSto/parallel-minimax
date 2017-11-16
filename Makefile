CPPFLAGS=-std=c++11 -g

GAMES_DIR=src/games/

connect-four: $(GAMES_DIR)/connectfour.cpp $(GAMES_DIR)/connectfour.h
	g++ $(CPPFLAGS) -O3 -o connect-four $(GAMES_DIR)/connectfour.cpp

clean:
	rm connect-four