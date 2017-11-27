all: hw6

atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp

list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp

hw6: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h

ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainScanner.o list.o atom.o -lgtest
else
	g++ -o hw6 mainScanner.o list.o atom.o -lgtest -lpthread
endif
	
	
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
		g++ -std=c++11 -c mainScanner.cpp

clean:
	rm -f *.o hw6
stat:
	wc *.h *.cpp
