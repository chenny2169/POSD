INC_DIR = include

all: hw1

hw1: main.o Media.o Shapes.o
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o Media.o Shapes.o -lgtest
else
	g++ -o hw1 main.o Media.o Shapes.o -lgtest -lpthread
endif
	
main.o: $(INC_DIR)/Sort.h $(INC_DIR)/Shapes.h $(INC_DIR)/Media.h main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp
Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif