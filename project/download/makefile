main:main.o HttpDown.o HttpOperation.o
	g++ main.o HttpOperation.o HttpDown.o -lpthread -g -l ssl -l crypto -o main
main.o:main.cpp
	g++ -c main.cpp
HttpOperation.o:HttpOperation.cpp HttpOperation.h
	g++ -c HttpOperation.cpp
HttpDown.o:HttpDown.cpp HttpDown.h
	g++ -c HttpDown.cpp 
clean:
	rm *.o
