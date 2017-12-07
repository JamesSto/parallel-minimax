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

default : 
	$(CC) $(PROF) $(LFLAGS) $(GAMES_DIR)/connectfour.cpp -o game

parallel : $(PARALLEL_OBJS)
	$(CC) $(PROF) $(LFLAGS) $(PARALLEL_OBJS) -o game

tuned : $(TUNED_OBJS)
	$(CC) $(PROF) $(LFLAGS) $(TUNED_OBJS) -o game

naive : $(NAIVE_OBJS)
	$(CC) $(PROF) $(LFLAGS) $(NAIVE_OBJS) -o game

task : $(TASK_OBJS)
	$(CC) $(PROF) $(LFLAGS) $(TASK_OBJS) -o game

connectfour.o : $(GAMES_DIR)/connectfour.h  $(GAMES_DIR)/connectfour.cpp
	$(CC) $(PROF) $(CPPFLAGS) $(GAMES_DIR)/connectfour.cpp

naiveminimax.o : $(MINIMAX_DIR)/minimax.h $(MINIMAX_DIR)/naiveminimax.cpp 
	$(CC) $(PROF) $(CPPFLAGS) $(MINIMAX_DIR)/minimax.h -o naiveminimax.o

tunedminimax.o : $(MINIMAX_DIR)/minimax.h $(MINIMAX_DIR)/tunedminimax.cpp 
	$(CC) $(PROF) $(CPPFLAGS) $(MINIMAX_DIR)/tunedminimax.cpp -o tunedminimax.o

parallelminimax.o :  $(MINIMAX_DIR)/minimax.h $(MINIMAX_DIR)/parallelminimax.cpp 
	$(CC) $(PROF) $(CPPFLAGS) $(MINIMAX_DIR)/parallelminimax.cpp -o parallelminimax.o

taskminimax.o :  $(MINIMAX_DIR)/minimax.h $(MINIMAX_DIR)/taskminimax.cpp 
	$(CC) $(PROF) $(CPPFLAGS) $(MINIMAX_DIR)/taskminimax.cpp -o taskminimax.o


clean:
	rm *.o game