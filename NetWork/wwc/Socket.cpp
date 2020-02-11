#include "Socket.h"
Socket::Socket()
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);    
}

Socket::Socket(int fd)
{
    sockfd = fd;
}


void Socket::bindAddress(struct sockaddr_in addr)
{
    int flag = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEPORT,&flag,sizeof flag); 
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

    if(connfd > 0)
        return connfd;
    return -1;
}

Socket::~Socket()
{
    shutdown();
}

//获取本地网卡接口地址;
struct sockaddr_in Socket::GetLocalAddr()
{
    int sawfd = socket(AF_INET,SOCK_RAW,0);
    struct ifreq ifr;
    bzero(&ifr,sizeof ifr);
    memcpy(ifr.ifr_name,"wlp4s0",strlen("wlp4s0"));
    ioctl(sawfd,SIOCGIFADDR,&ifr);
    
    return *(struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr;
}

void Socket::shutdown()
{
    ::close(sockfd);
}
