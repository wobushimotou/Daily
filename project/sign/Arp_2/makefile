main:main.o Arp.o
	g++ main.o Arp.o -o main -lpthread
main.o:
	g++ -c main.cpp -o main.o
Arp.o:
	g++ -c Arp.cpp -o Arp.o
clean:
	rm *.o;
