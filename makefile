all: hw2

hw2: main.o atom.o number.o variable.o
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest -lpthread

main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp

variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp