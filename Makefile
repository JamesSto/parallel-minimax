NAIVE_OBJS=naiveminimax.o connectfour.o
TUNED_OBJS=tunedminimax.o connectfour.o
PARALLEL_OBJS=parallelminimax.o connectfour.o
TASK_OBJS=taskminimax.o connectfour.o
CC = g++
DEBUG = -g
CPPFLAGS = -std=c++14 -Wall -c -O3 -g -fopenmp -DUSE_EXPORT_KEYWORD
LFLAGS = -Wall -fopenmp $(DEBUG)
PROF = -pg

GAMES_DIR=src/games
MINIMAX_DIR=src/minimax

tuned : 
	$(CC) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DTUNED -o game

naive : 
	$(CC) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DNAIVE -o game

task : 
	$(CC) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DTASK -o game

parallel : 
	$(CC) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -DPARALLEL -o game


clean:
	rm *.o game