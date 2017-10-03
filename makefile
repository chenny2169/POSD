all: hw2

hw2: MainNumber.o Number.o Atom.o Variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 MainNumber.o Number.o Atom.o Variable.o -lgtest
else
	g++ -o hw2 MainNumber.o Number.o Atom.o Variable.o -lgtest -lpthread
endif

MainNumber.o: MainNumber.cpp utTerm.h
	g++ -std=gnu++0x -c MainNumber.cpp
Number.o: Number.cpp atom.h variable.h number.h
	g++ -std=gnu++0x -c Number.cpp
Atom.o: Atom.cpp atom.h variable.h number.h
	g++ -std=gnu++0x -c Atom.cpp
Variable.o: Variable.cpp atom.h variable.h number.h
	g++ -std=gnu++0x -c Variable.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp
