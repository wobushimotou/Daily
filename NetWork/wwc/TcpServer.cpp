#include <iostream>
#include "TcpServer.h"

TcpServer::TcpServer(std::shared_ptr<EventLoop> loop,int port,std::string namearg)
    :loop(loop),
    name(namearg),
    acceptor(new Acceptor(loop,port)),
    connectionCallback(NULL),
    messageCallback(NULL),
    started(false),
    nextConnId(1),
    threadpool(new EventLoopThreadPool(loop))
{
    acceptor->setNewConnectionCallback(
        std::bind(&TcpServer::NewConnection,this,std::placeholders::_1,std::placeholders::_2));
}

void TcpServer::NewConnection(int sockfd,struct sockaddr_in addr)
{
    
    printf("NewConnection fd = %d thread = %ld\n",sockfd,syscall(SYS_gettid));
    char buf[64];
    //为新创建的TcpConnection对象起名
    snprintf(buf,sizeof buf,"-%s#:%d",inet_ntoa(addr.sin_addr),nextConnId);

    ++nextConnId;
    std::string connName = buf+name;

    auto ioLoop = threadpool->getNextLoop();
    TcpConnectionPtr conn = std::make_shared<TcpConnection>(ioLoop,connName,sockfd);

    connections[connName] = conn;
    conn->setConnectionCallback(connectionCallback);
    conn->setMessageCallback(messageCallback);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnction,this,std::placeholders::_1));
    conn->setwriteCompleteCallback(writeCompleteCallback_);

    printf("Channel = %p\n",conn->channel.get());
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished,conn));
}



void TcpServer::removeConnction(const TcpConnectionPtr &conn)
{
    printf("TcpServer::removeConnction\n");
    loop->runInLoop(std::bind(&TcpServer::removeConnctionInLoop,this,conn));
}

void TcpServer::removeConnctionInLoop(const TcpConnectionPtr &conn)
{
    printf("TcpServer::removeConnctionInLoop\n");
    size_t n = connections.erase(conn->name());
    assert(n == 1);
    std::shared_ptr<EventLoop> ioLoop = conn->getLoop();
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestoryed,conn));
}

TcpServer::~TcpServer()
{
    printf("~TcpServer()\n");
}

void TcpServer::start()
{
    threadpool->start();
    loop->runInLoop(std::bind(&Acceptor::listen,acceptor.get()));
}

