all: clean main run

main: main.cpp Rubik.o MinHeap.o
	g++ -g -o main Rubik.o MinHeap.o main.cpp

Rubik.o: Rubik.cpp Rubik.h
	g++ -g -c Rubik.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	g++ -g -c MinHeap.cpp

clean:
	rm -f main *.o

run:
	./main