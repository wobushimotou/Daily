#include "Socket.h"
Socket::Socket()
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);    
}

void Socket::bindAddress(struct sockaddr_in addr)
{
    socklen_t addrlen = sizeof addr;
    if(bind(sockfd,(struct sockaddr *)&addr,addrlen) < 0) {

    }

}

void Socket::SetNonblock()
{
    int flag = fcntl(sockfd,F_GETFL);
    flag |= O_NONBLOCK;
    if(fcntl(sockfd,F_SETFL,flag) < 0) {
        std::cout << "设置非阻塞套接字失败\n";
    }
}

void Socket::listenAddr()
{
    if(::listen(sockfd,SOMAXCONN) < 0) {
        std::cout << "开启监听套接字失败\n";
    }
}

int Socket::acceptAddr(struct sockaddr_in *addr)
{
        
}

