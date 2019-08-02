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
    }
}

void Socket::listenAddr()
{
    if(::listen(sockfd,SOMAXCONN) < 0) {
    }
}

int Socket::acceptAddr(struct sockaddr_in *addr)
{
    socklen_t len = sizeof addr;
    bzero(&addr,sizeof addr);        
    int connfd = ::accept(sockfd,(sockaddr *)addr,&len);
    if(connfd >= 0)
        return connfd;
    return -1;
}

Socket::~Socket()
{
}

Socket::Socket(int fd)
{
    sockfd = fd;
}

