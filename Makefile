NAIVE_OBJS = naiveminimax.o connectfour.o
TUNED_OBJS = tunedminimax.o connectfour.o
PARALLEL_OBJS = parallelminimax.o connectfour.o
TASK_OBJS = taskminimax.o connectfour.o
CC = g++
DEBUG = -g
CPPFLAGS = -pg -std=c++11 -Wall -O3 -fopenmp
LFLAGS = -Wall -fopenmp -pg
PROF = -pg

GAMES_DIR=src/games
MINIMAX_DIR=src/minimax

tuned : 
	$(CC) $(CPPFLAGS) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DTUNED -o game

naive : 
	$(CC) $(CPPFLAGS) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DNAIVE -o game

task : 
	$(CC) $(CPPFLAGS) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DTASK -o game

parallel : 
	$(CC) $(CPPFLAGS) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DPARALLEL -o game


clean:
	rm *.o game
