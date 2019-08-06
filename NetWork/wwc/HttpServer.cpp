#include <iostream>
#include "HttpServer.h"
using namespace std::placeholders;

HttpServer::HttpServer(EventLoop *loop,int port,std::string name)
    :server(loop,port,name)
{
    server.setConnectionCallback(std::bind(&HttpServer::onConnection,this,_1));
    TcpServer::MessageCallback f = std::bind(&HttpServer::onMessage,this,_1,_2,_3);
    server.setMessageCallback(f);
}

void HttpServer::onConnection(const TcpServer::TcpConnectionPtr &conn)
{
    std::cout << "HttpServer::onConnection()" << std::endl;
    if(conn->connected()) {
        std::cout << "new client conneded:" << conn->socket->fd() << std::endl;;
    }

}

void HttpServer::onMessage(const TcpServer::TcpConnectionPtr &conn,Buffer *buf,size_t size)
{
    std::cout << "HttpServer::onMessage()" << std::endl;
    std::string head;
    buf->retrieveAllAsString(head);
    int b = 0;
    int e = head.find(" ",0);

    if(head.substr(b,e-b) == "GET") {
        std::string filename = this->onGet(head);
        if(filename.size() == 0) {
            filename = "test.html";
        }
        std::cout << filename << std::endl;

        std::fstream file(filename);
        std::string data;
        int i = 0;
        char ch;
        while(file.read(&ch,1)) {
            data.push_back(ch);
            ++i;
        }
        data += "\r\n\r\n";
        
        file.close();

        std::string Requesthead = std::string("HTTP/1.1 200 OK\r\n")+ \
           "Content-Type: text/html;charset=utf-8\r\n"+ \
            "Content-Length: "+std::to_string(i) + "\r\n"+ \
            "Connection: keep-alive\r\n" + \
            "Cache-Control:max-age=-1\r\n" + \
            "Server: nginx/1.8.0\r\n"+"\r\n";

        conn->send(Requesthead);
        conn->send(data);
    }
    

}

void HttpServer::start() 
{
    server.start();
}

std::string HttpServer::onGet(std::string buff) {
    size_t begin = buff.find("Referer");
    if(begin == std::string::npos)
        return "";
    size_t end = buff.find("\r\n",begin);
    int i = buff.substr(begin,end-begin).find_last_of("/");
    return buff.substr(begin,end-begin).substr(i+1,end-begin-i);
}
