CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

all: cTreeTest tTreeTest
	
cTreeTest: cTreeTest.o CTree.o
	$(CC) -o cTreeTest cTreeTest.o CTree.o


cTreeTest.o: cTreeTest.cpp 
	$(CC) $(CFLAGS) -c cTreeTest.cpp

CTree.o: CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTree.cpp

# TTree Stuff
tTreeTest: tTreeTest.o
	$(CC) -o tTreeTest tTreeTest.o 

tTreeTest.o: tTreeTest.cpp Tree.h 
	$(CC) $(CFLAGS) -c tTreeTest.cpp



# Removes all object files and the executable named main,
# so we can start fresh
clean:
	rm -f *.o cTreeTest tTreeTest


