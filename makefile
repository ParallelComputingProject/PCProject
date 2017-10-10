CPPFLAGS=-std=c++11 -fopenmp

all:
	g++ main.cpp $(CPPFLAGS) -o k.o
