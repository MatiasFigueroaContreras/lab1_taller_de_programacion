all: clean test_HashTable test_MinHeap run

main: main.cpp Rubik.o MinHeap.o
	g++ -g -o main Rubik.o MinHeap.o main.cpp

test_MinHeap: test_MinHeap.cpp Rubik.o MinHeap.o State.o
	g++ -g -o test_MinHeap Rubik.o MinHeap.o State.o test_MinHeap.cpp

test_HashTable: test_HashTable.cpp Rubik.o HashTable.o LinkedList.o Node.o
	g++ -g -o test_HashTable Rubik.o HashTable.o LinkedList.o Node.o test_HashTable.cpp

Rubik.o: Rubik.cpp Rubik.h
	g++ -g -c Rubik.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	g++ -g -c MinHeap.cpp

State.o: State.cpp State.h
	g++ -g -c State.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -g -c HashTable.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -g -c LinkedList.cpp

Node.o: Node.cpp Node.h
	g++ -g -c Node.cpp

clean:
	rm -f main test_MinHeap test_HashTable *.o

run:
	./test_HashTable
	./test_MinHeap
