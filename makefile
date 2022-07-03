all:
	g++ -std=c++11 -Wall -Wextra -o program *.cpp

clean:
	rm program output.fasta

run: all

