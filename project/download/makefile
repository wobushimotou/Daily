main:main.o HttpDown.o myhttp_down.o
	g++ main.o HttpDown.o myhttp_down.o
main.o:main.cpp
	g++ -c main.cpp
HttpDown.o:HttpDown.cpp myhttp_down.cpp
	g++ -c HttpDown.cpp myhttp_down.cpp
myhttp_down.o:myhttp_down.cpp
	g++ -c myhttp_down.cpp
clear:
	rm *.o
