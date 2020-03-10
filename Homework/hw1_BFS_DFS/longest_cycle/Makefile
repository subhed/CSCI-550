run: main.o  graph.o 
	g++ -o run main.o  graph.o 
graph.o: graph.cpp graph.h  timestamp.h
	g++ -c -Wall -pedantic -g -std=c++11 graph.cpp
main.o: main.cpp  graph.h 
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o graph.o run
