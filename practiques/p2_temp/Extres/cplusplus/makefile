all: main.cc pointers.cc simplex_primal.cc
	g++ main.cc pointers.cc simplex_primal.cc -Wall -o program -std=c++11
debug: main.cc pointers.cc simplex_primal.cc
	g++ main.cc pointers.cc simplex_primal.cc -g -Wall -o program_debug -std=c++11
clean:
	rm -f program program_debug
