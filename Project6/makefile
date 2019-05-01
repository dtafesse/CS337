chatter: MySocket.o main.o
	g++ MySocket.o main.o -o chatter
MySocket.o: MySocket.h MySocket.cpp
	g++ -c MySocket.cpp
main: main.h main.cpp MySocket.h  
	g++ -c main.cpp

