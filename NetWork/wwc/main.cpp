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
EventLoop loop;
void onConnection(std::shared_ptr<TcpConnection> conn) {
    printf("onConnection():new connection\n");
}

void onMessage(std::shared_ptr<TcpConnection> conn,char *data,size_t n) {
    
    printf("onMessagea():received %zd bytes\ndata:%s",n,data);
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

