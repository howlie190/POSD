all: hw2

hw2: main.o atom.o number.o variable.o
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest -lpthread

main.o: main.cpp utTerm.h
	g++ --std=c++11 utTerm.h -c main.cpp

atom.o: atom.cpp Atom.h
	g++ --std=c++11 Atom.h -c atom.cpp

number.o: number.cpp Number.h
	g++ --std=c++11 -c Number.h number.cpp

variable.o: variable.cpp Variable.h
	g++ --std=c++11 -c Variable.h variable.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp