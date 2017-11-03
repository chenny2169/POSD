all: hw5

hw5: mainTerm.o term.o
ifeq (${OS}, Windows_NT)
		g++ -o hw5 mainTerm.o term.o -lgtest
else
		g++ -o hw5 mainTerm.o term.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utAtom.h utStruct.h utVariable.h utList.h utScanner.h utParser.h
	g++ -std=gnu++0x -c mainTerm.cpp
term.o: term.cpp term.h variable.h
	g++ -std=gnu++0x -c term.cpp

clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp
