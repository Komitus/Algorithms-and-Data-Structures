main: main.o tools.o
	g++ main.o tools.o -o main
main.o: main.cpp 
	g++ -c -O3 main.cpp
tools.o: tools.cpp
	g++ -c -O3 tools.cpp

clean: 
	rm *.o main *.csv
