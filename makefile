all: hw7

hw7: mainTerm.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
		g++ -o hw7 mainTerm.o term.o struct.o list.o -lgtest
else
		g++ -o hw7 mainTerm.o term.o struct.o list.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utAtom.h utStruct.h utVariable.h utList.h utScanner.h utParser.h utIterator.h
	g++ -std=gnu++0x -c mainTerm.cpp
term.o: term.cpp term.h variable.h iterator.h
	g++ -std=gnu++0x -c term.cpp
struct.o: struct.cpp struct.h iterator.h
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h iterator.h
	g++ -std=gnu++0x -c list.cpp

clean:
	rm -f *.o hw7
stat:
	wc *.h *.cpp
