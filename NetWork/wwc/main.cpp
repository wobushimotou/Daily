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
EventLoop loop;
void newConnectionCallback(int sockfd,struct sockaddr_in addr) {
    std::cout << "newConnectionCallback():一号服务器" << std::endl;
    ::write(sockfd,"How are you?\n",14);
    close(sockfd);
}
void f2(int sockfd,struct sockaddr_in addr) {
    std::cout << "newConnectionCallback():二号服务器" << std::endl;
    ::write(sockfd,"I'am fine\n",10);
    close(sockfd);
}

int main()
{
    
    Acceptor ac(&loop,9981);
    Acceptor ac2(&loop,8864);
    ac.setNewConnectionCallback(newConnectionCallback);
    ac2.setNewConnectionCallback(f2);
    ac.listen();
    ac2.listen();
    loop.loop();
    return 0;
}

