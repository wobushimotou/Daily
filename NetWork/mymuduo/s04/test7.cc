#include <iostream>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/Acceptor.h>
#include <muduo/net/SocketsOps.h>
#include <muduo/base/Timestamp.h>
void NewConnection(int sockfd,const muduo::net::InetAddress peerAddr) {
    printf("new NewConnection():acceptd a new connection from %s\n",peerAddr.toIpPort().c_str());
    std::string message = muduo::Timestamp::now().toFormattedString();
    ::write(sockfd,message.c_str(),message.size()-1);
    muduo::net::sockets::close(sockfd); 
}

int main()
{
    printf("main():pid = %d\n",getpid());

    muduo::net::InetAddress listenAddr(9981);
    muduo::net::EventLoop loop;

    muduo::net::Acceptor acceptor(&loop,listenAddr,true);
    acceptor.setNewConnectionCallback(NewConnection);
    acceptor.listen();

    loop.loop();
    return 0;
}

