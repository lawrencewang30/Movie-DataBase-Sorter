#Makefile
CXX_FLAG = --std=c++11 -g

all: runMovies

runMovies: movies.o main.o
	g++ $(CXX_FLAG) -o runMovies movies.o main.o

runMovies.o: movies.cpp
	g++ -c $(CXX_FLAG) movies.cpp

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

movies.o: movies.cpp
	g++ -c $(CXX_FLAG) movies.cpp


clean:
	rm -f runMovies *.o
