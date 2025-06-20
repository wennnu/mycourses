run: main.o mycourse.o
	g++ main.o mycourse.o -o run

main.o: main.cpp
	g++ -c main.cpp

mycourse.o: mycourse.cpp mycourse.h
	g++ -c mycourse.cpp
