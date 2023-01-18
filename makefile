CC	= g++ -Wall -pedantic -std=c++11 -pthread -O3

all: collatz

collatz.o: collatz.cpp
	$(CC) -c collatz.cpp

collatz: collatz.o
	$(CC) -o collatz collatz.o

# -----
# clean by removing object files.

clean:
	rm collatz.o collatz
