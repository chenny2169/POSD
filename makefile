all: hw4

hw4: MainTerm.o Term.o
ifeq (${OS}, Windows_NT)
		g++ -o hw4 MainTerm.o Term.o -lgtest
else
		g++ -o hw4 MainTerm.o Term.o -lgtest -lpthread
endif

MainTerm.o: MainTerm.cpp utAtom.h utStruct.h utVariable.h utList.h
	g++ -std=gnu++0x -c MainTerm.cpp
Term.o: Term.cpp term.h variable.h
	g++ -std=gnu++0x -c Term.cpp

clean:
	rm -f *.o hw4
stat:
	wc *.h *.cpp
