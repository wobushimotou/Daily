#include "Acceptor.h"
Acceptor::Acceptor(std::shared_ptr<EventLoop> loop,int port)
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
    int connfd = acceptSocket.acceptAddr(&sockaddr);
    if(connfd > 0) {
        if(newConnectionCallback_) {
            newConnectionCallback_(connfd,sockaddr);
        }
        else {
        }
    }
    else {
        printf("Acceptor::handleRead error\n");
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
    acceptChannel.disableAll();
    acceptChannel.remove();
}

