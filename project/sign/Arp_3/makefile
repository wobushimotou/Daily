Server:Sign_Server.o Arp.o Client
	g++ Sign_Server.o Arp.o -o Server -lpthread
Client:Sign_Client.o Arp.o
	g++ Sign_Client.o Arp.o -o Client -lpthread
Arp.o:
	g++ -c Arp.cpp -o Arp.o
Sign_Server.o:
	g++ -c Sign_Server.cpp -o Sign_Server.o
Sign_Client.o:
	g++ -c Sign_Client.cpp -o Sign_Client.o
clean:
	rm *.o;
