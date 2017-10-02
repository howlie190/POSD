all: hw2

hw2: main.o atom.o number.o variable.o
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest -lpthread

main.o: main.cpp utTerm.h
	g++ --std=c++11 utTerm.h main.cpp

atom.o: atom.cpp Atom.h
	g++ --std=c++11 Atom.h atom.cpp

number.o: number.cpp Number.h
	g++ --std=c++11 Number.h number.cpp

variable.o: variable.cpp Variable.h
	g++ --std=c++11 Variable.h variable.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp