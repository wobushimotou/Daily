server:main.o EventLoop.o Channel.o epoll.o Acceptor.o Socket.o TcpConnection.o TcpServer.o Buffer.o HttpServer.o EventLoopThreadPool.o
	g++ main.o EventLoop.o Channel.o epoll.o Acceptor.o Socket.o TcpConnection.o TcpServer.o Buffer.o HttpServer.o EventLoopThreadPool.o -o server -g -lpthread
EventLoop.o:EventLoop.cpp EventLoop.h Channel.h ./poll/epoll.h
	g++ -c EventLoop.cpp
Channel.o:Channel.cpp Channel.h EventLoop.h 
	g++ -c Channel.cpp
epoll.o:./poll/epoll.cpp EventLoop.h Channel.h ./poll/epoll.h
	g++ -c ./poll/epoll.cpp
Acceptor.o:Acceptor.cpp Acceptor.h EventLoop.h Socket.h
	g++ -c Acceptor.cpp
Socket.o:Socket.cpp Socket.h
	g++ -c Socket.cpp
TcpServer.o:TcpServer.cpp TcpServer.h EventLoop.h Acceptor.h TcpConnection.h  Buffer.h
	g++ -c TcpServer.cpp
TcpConnection.o:TcpConnection.cpp TcpConnection.h EventLoop.h Socket.h Channel.h Buffer.h
	g++ -c TcpConnection.cpp
Buffer.o:Buffer.cpp Buffer.h 
	g++ -c Buffer.cpp
EventLoopThreadPool.o:EventLoopThreadPool.cpp EventLoopThreadPool.h EventLoop.h
	g++ -c EventLoopThreadPool.cpp
HttpServer.o:HttpServer.cpp HttpServer.h EventLoop.h TcpServer.h
	g++ -c HttpServer.cpp
clean:
	rm *.o
