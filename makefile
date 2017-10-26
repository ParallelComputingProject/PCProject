CPPFLAGS=-Wall -std=c++11 -fopenmp

all:
	g++ main_p.cpp $(CPPFLAGS) -o k.o

clean:
	rm -rf *.o data.txt data2.txt input.txt test1.txt