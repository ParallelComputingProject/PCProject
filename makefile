CPPFLAGS=-std=c++11 -fopenmp

all:
	g++ k_means.cpp $(CPPFLAGS) -o k.o
