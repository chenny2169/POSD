all: hw2

hw2: mainNumber.o Number.o Atom.o Variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainNumber.o Number.o Atom.o Variable.o -lgtest
else
	g++ -o hw2 mainNumber.o Number.o Atom.o Variable.o -lgtest -lpthread
endif

mainNumber.o: mainNumber.cpp utTerm.h
	g++ -std=gnu++0x -c mainNumber.cpp
Number.o: Number.cpp Atom.h Variable.h Number.h
	g++ -std=gnu++0x -c Number.cpp
Atom.o: Atom.cpp Atom.h Variable.h Number.h
	g++ -std=gnu++0x -c Atom.cpp
Variable.o: Variable.cpp Atom.h Variable.h Number.h
	g++ -std=gnu++0x -c Variable.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp
