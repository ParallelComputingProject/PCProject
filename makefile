CPPFLAGS=-std=c++11 -fopenmp

all:
	g++ main_p.cpp $(CPPFLAGS) -o k.o
