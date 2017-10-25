all: hw4

hw4: main.o atom.o variable.o struct.o number.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o atom.o variable.o struct.o number.o list.o -lgtest
else
	g++ -o hw4 main.o atom.o variable.o struct.o number.o list.o -lgtest -lpthread
endif

main.o: main.cpp utList.h #utVariable.h utStruct.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp

struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp

list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif