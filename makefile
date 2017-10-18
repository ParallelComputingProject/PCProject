CPPFLAGS=-std=c++11 -fopenmp

all:
	g++ mainParallel.cpp $(CPPFLAGS) -o k.o
