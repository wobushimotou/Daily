server:main.o EventLoop.o Channel.o log.o epoll.o Acceptor.o Socket.o TcpConnection.o TcpServer.o Buffer.o
	g++ main.o EventLoop.o Channel.o log.o epoll.o Acceptor.o Socket.o TcpConnection.o TcpServer.o Buffer.o -o server -g
EventLoop.o:EventLoop.cpp EventLoop.h Channel.h ./log/log.h ./poll/epoll.h
	g++ -c EventLoop.cpp
Channel.o:Channel.cpp Channel.h EventLoop.h ./log/log.h
	g++ -c Channel.cpp
epoll.o:./poll/epoll.cpp EventLoop.h Channel.h ./log/log.h ./poll/epoll.h
	g++ -c ./poll/epoll.cpp
log.o:./log/log.cpp ./log/log.h
	g++ -c ./log/log.cpp
Acceptor.o:Acceptor.cpp Acceptor.h EventLoop.h Socket.h
	g++ -c Acceptor.cpp
Socket.o:Socket.cpp Socket.h
	g++ -c Socket.cpp
TcpServer.o:TcpServer.cpp TcpServer.h EventLoop.h Acceptor.h TcpConnection.h  Buffer.h
	g++ -c TcpServer.cpp
TcpConnection.o:TcpConnection.cpp TcpConnection.h EventLoop.h Socket.h Channel.h Buffer.h
	g++ -c TcpConnection.cpp
Buffer.o:Buffer.cpp Buffer.h 
	g++ -c Buffer.cpp;
clean:
	rm *.o
