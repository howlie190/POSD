all: hw2
hw2: main.o
	g++ -o main.o -lgtest -lpthread
main.o: main.cpp utTerm.h
	g++ -std=c++11 -c main.cpp
clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp