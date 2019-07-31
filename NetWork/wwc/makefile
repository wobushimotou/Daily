server:main.o EventLoop.o Channel.o log.o epoll.o Acceptor.o Socket.o
	g++ main.o EventLoop.o Channel.o log.o epoll.o Acceptor.o Socket.o -o server
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
clean:
	rm *.o
