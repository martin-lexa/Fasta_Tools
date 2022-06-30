all: test.cpp
	g++ -std=c++11 -Wall -Wextra -o program test.cpp

clean:
	rm program

run: all

