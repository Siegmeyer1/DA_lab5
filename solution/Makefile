all: solution

solution: solution.o SuffixTree.o
	g++ -std=c++11 -O3 solution.o SuffixTree.o -o solution

solution.o: solution.cpp
	g++ -std=c++11 -O3 -c solution.cpp

SuffixTree.o: SuffixTree.cpp
	g++ -std=c++11 -O3 -c SuffixTree.cpp

clean:
	rm -rf *.o solution
