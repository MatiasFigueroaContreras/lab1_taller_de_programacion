FLAGS = -O2 -g -Wall

all: clean test_Rubik test_RubikSolver test_MinHeap test_HashTable test_LinkedList test_Node test_State run

main: main.cpp RubikSolver.o Rubik.o MinHeap.o HashTable.o State.o LinkedList.o Node.o
	g++ $(FLAGS) -o main RubikSolver.o Rubik.o MinHeap.o HashTable.o State.o LinkedList.o Node.o main.cpp

test_Rubik: test_Rubik.cpp Rubik.o
	g++ $(FLAGS) -o test_Rubik Rubik.o test_Rubik.cpp

test_RubikSolver: test_RubikSolver.cpp RubikSolver.o Rubik.o MinHeap.o HashTable.o State.o LinkedList.o Node.o
	g++ $(FLAGS) -o test_RubikSolver RubikSolver.o Rubik.o MinHeap.o HashTable.o State.o LinkedList.o Node.o test_RubikSolver.cpp

test_MinHeap: test_MinHeap.cpp Rubik.o MinHeap.o State.o
	g++ $(FLAGS) -o test_MinHeap Rubik.o MinHeap.o State.o test_MinHeap.cpp

test_HashTable: test_HashTable.cpp Rubik.o HashTable.o LinkedList.o Node.o
	g++ $(FLAGS) -o test_HashTable Rubik.o HashTable.o LinkedList.o Node.o test_HashTable.cpp

test_LinkedList: test_LinkedList.cpp Rubik.o LinkedList.o Node.o
	g++ $(FLAGS) -o test_LinkedList Rubik.o LinkedList.o Node.o test_LinkedList.cpp

test_Node: test_Node.cpp Rubik.o Node.o
	g++ $(FLAGS) -o test_Node Rubik.o Node.o test_Node.cpp

test_State: test_State.cpp Rubik.o State.o
	g++ $(FLAGS) -o test_State Rubik.o State.o test_State.cpp

Rubik.o: Rubik.cpp Rubik.h
	g++ $(FLAGS) -c Rubik.cpp

RubikSolver.o: RubikSolver.cpp RubikSolver.h
	g++ $(FLAGS) -c RubikSolver.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	g++ $(FLAGS) -c MinHeap.cpp

State.o: State.cpp State.h
	g++ $(FLAGS) -c State.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ $(FLAGS) -c HashTable.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ $(FLAGS) -c LinkedList.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

clean:
	rm -f main test_Rubik test_RubikSolver test_MinHeap test_HashTable test_LinkedList test_Node test_State *.o

run:
	./test_Rubik
	./test_RubikSolver
	./test_MinHeap
	./test_HashTable
	./test_LinkedList
	./test_Node
	./test_State
