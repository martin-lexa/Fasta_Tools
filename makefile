all:
	g++ -std=c++11 -Wall -Wextra -o program *.cpp *.h

clean:
	rm program

run: all

