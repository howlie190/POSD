all: hw3

hw3: main.o atom.o variable.o struct.o number.o

ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o atom.o variable.o struct.o number.o -lgtest
else
	g++ -o hw3 main.o atom.o variable.o struct.o number.o -lgtest -lpthread
endif

main.o: main.cpp utVariable.h utStruct.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp

struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif