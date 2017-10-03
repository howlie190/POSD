all: hw2

hw2: main.o atom.o number.o variable.o

ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest
else
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest -lpthread
endif
main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp

variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif