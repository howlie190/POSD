all: hw4

hw4: main.o basic.o

ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o basic.o -lgtest
else
	g++ -o hw4 main.o basic.o -lgtest -lpthread
endif

main.o: main.cpp utVariable.h utStruct.h utList.h
	g++ -std=gnu++0x -c main.cpp

basic.o: basic.cpp basic.h
	g++ -std=gnu++0x -c basic.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif