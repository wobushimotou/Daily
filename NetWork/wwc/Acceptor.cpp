#include "Acceptor.h"
Acceptor::Acceptor(EventLoop *loop,int port)
    :loop(loop),
    acceptSocket(1),
    acceptChannel(loop,acceptSocket.fd()),
    port(port),
    listening_(false)
{
    initAddr();
    acceptSocket.SetNonblock();
    acceptSocket.bindAddress(addr);

    acceptChannel.setReadCallback(std::bind(&Acceptor::handleRead,this));
    sock = open("dev/null",O_RDWR);
}


void Acceptor::initAddr()
{

    /* addr.sin_addr.s_addr = htons(INADDR_ANY); */
    /* addr.sin_family = AF_INET; */
    /* addr.sin_port = htons(this->port); */
    
    addr = acceptSocket.GetLocalAddr();
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
}

void Acceptor::handleRead()
{
    struct sockaddr_in sockaddr;
    int connfd = acceptSocket.acceptAddr(&sockaddr,sock);
    sock = open("/dev/null",O_RDWR);
    if(connfd > 0) {
        if(newConnectionCallback_) {
            newConnectionCallback_(connfd,sockaddr);
        }
        else {
            ::close(connfd);
        }
    }
    else {
    }
}

void Acceptor::listen()
{
    loop->isInLoopThread();
    listening_ = true;
    acceptSocket.listenAddr();
    acceptChannel.enableReading();
}


Acceptor::~Acceptor()
{
    acceptSocket.~Socket(); 
}

