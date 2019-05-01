a.out: digtalTime.o timeInterval.o DaysOfWeek.o Course.o main.o
	g++ digialTime.o timeInterval.o DaysOfWeek.o Course.o main.o -o a.out
digtalTime.o: digtalTime.h digtalTime.cpp
	g++ -c digialTime.cpp
timeInterval.o: timeInterval.h timeInterval.cpp digtalTime.h
	g++ -c timeInterval.cpp
DaysOfWeek.o: DaysOfWeek.h DaysOfWeek.cpp
	g++ -c DaysOfWeek.cpp
Course.o: Course.h Course.cpp timeInterval.h DaysOfWeek.h
	g++ -c Course.cpp
main: main.h main.cpp Course.h  
	g++ -c main.cpp

