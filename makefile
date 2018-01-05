all: hw8 shell

hw8: mainTerm.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
		g++ -o hw8 mainTerm.o term.o struct.o list.o -lgtest
else
		g++ -o hw8 mainTerm.o term.o struct.o list.o -lgtest -lpthread
endif

shell: shell.o
ifeq (${OS}, Windows_NT)
		g++ -o shell shell.o -lgtest
else
		g++ -o shell shell.o -lgtest -lpthread
endif


mainTerm.o: mainTerm.cpp utAtom.h utStruct.h utVariable.h utList.h utScanner.h utParser.h utIterator.h expression.h exception.h
	g++ -std=gnu++0x -c mainTerm.cpp
term.o: term.cpp term.h variable.h iterator.h
	g++ -std=gnu++0x -c term.cpp
struct.o: struct.cpp struct.h iterator.h
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h iterator.h
	g++ -std=gnu++0x -c list.cpp
shell.o: shell.cpp scanner.h parser.h
	g++ -std=gnu++0x -c shell.cpp

clean:
	rm -f *.o hw8 shell
stat:
	wc *.h *.cpp
