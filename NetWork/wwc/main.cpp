#include <iostream>
#include <string.h>
#include "./log/log.h"
#include "EventLoop.h"
#include <sys/timerfd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Acceptor.h"
#include "TcpServer.h"
#include "Buffer.h"
EventLoop loop;
void onConnection(std::shared_ptr<TcpConnection> conn) {
    printf("onConnection():new connection\n");
}

void onMessage(std::shared_ptr<TcpConnection> conn,Buffer &data,size_t n) {
    std::string buff;
    data.retrieveAll(buff);
    std::cout << buff << std::endl;
    buff.clear();
}
int main()
{
    TcpServer server(&loop,9981,"wh");
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
    return 0;
}

