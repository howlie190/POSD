all: hw7

hw7: mainIterator.o atom.o list.o struct.o

ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o list.o atom.o struct.o -lgtest
else
	g++ -o hw7 mainIterator.o list.o atom.o struct.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
	g++ -std=gnu++0x -c mainScanner.cpp

mainIterator.o: mainIterator.cpp utIterator.h iterator.h atom.h struct.h variable.h list.h
	g++ -std=gnu++0x -c mainIterator.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
	g++ -std=gnu++0x -c list.cpp

struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif