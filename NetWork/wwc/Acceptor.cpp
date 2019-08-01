#include "Acceptor.h"
Acceptor::Acceptor(EventLoop *loop,int port)
    :loop(loop),
    acceptSocket(),
    acceptChannel(loop,acceptSocket.fd()),
    port(port),
    listening_(false)
{
    initAddr();
    acceptSocket.SetNonblock();
    acceptSocket.bindAddress(addr);
    acceptChannel.setReadCallback(std::bind(&Acceptor::handleRead,this));
    std::cout << "Acceptor()\n";    
}


void Acceptor::initAddr()
{
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
}

void Acceptor::handleRead()
{
    std::cout << "Acceptor::hanleRead()\n";
    struct sockaddr_in sockaddr;
    int connfd = acceptSocket.acceptAddr(&sockaddr);
    if(connfd > 0) {
        if(newConnectionCallback_) {
            newConnectionCallback_(connfd,sockaddr);
        }
        else {
            std::cout << "close\n";
            ::close(connfd);
        }
    }
    else {
        std::cout << "in Acceptor handleRead() error" << std::endl;
    }
}

void Acceptor::listen()
{
    std::cout << "Acceptor::listen()\n";
    loop->isInLoopThread();
    listening_ = true;
    acceptSocket.listenAddr();
    acceptChannel.enableReading();
}


Acceptor::~Acceptor()
{
   acceptSocket.~Socket(); 
}

