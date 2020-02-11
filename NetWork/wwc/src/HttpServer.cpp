#include <iostream>
#include "HttpServer.h"
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

HttpServer::HttpServer(std::shared_ptr<EventLoop> loop,int port,std::string name)
    :server(loop,port,name)
{
    server.setConnectionCallback(std::bind(&HttpServer::onConnection,this,_1));
    TcpServer::MessageCallback f = std::bind(&HttpServer::onMessage,this,_1,_2,_3);
    server.setMessageCallback(f);
}

void HttpServer::onConnection(const TcpServer::TcpConnectionPtr &conn)
{
    if(conn->connected()) {
    }
}

void HttpServer::onMessage(const TcpServer::TcpConnectionPtr &conn,TcpConnection::BufferPtr buf,size_t size)
{
    std::string head;
    buf->retrieveAllAsString(head);
    int b = 0;
    int e = head.find(" ",0);
    if(head.substr(b,e-b) == "GET") {
        doGet(conn,head);    
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

int HttpServer::ReadFile(std::string filename)
{
    if(data[filename].size() > 0)
        return data[filename].size();
    std::fstream file(filename);
    int i = 0;
    char ch;
    std::string temp;
    while(file.read(&ch,1)) {
        /* data[filename].push_back(ch); */
        temp.push_back(ch);
        ++i;
    }
    data[filename] = temp;
    data[filename] += "\r\n\r\n";
    file.close();
    return i;
}

void HttpServer::doGet(const TcpServer::TcpConnectionPtr &conn,std::string head) {
    std::string filename = this->onGet(head);
    if(filename.size() == 0) {
        filename = "test.html";
    }
    int i = ReadFile(filename);
    std::string Requesthead = std::string("HTTP/1.1 200 OK\r\n")+ \
                              "Content-Type: text/html;charset=utf-8\r\n"+ \
                              "Content-Length: "+std::to_string(i) + "\r\n"+ \
                              "Connection: keep-alive\r\n" + \
                              "Cache-Control:max-age=-1\r\n" + \
                              "Server: nginx/1.8.0\r\n"+"\r\n";

    //发送响应头
    conn->send(Requesthead);
    //发送资源
    conn->send(data[filename]);
    //断开连接
    conn->connectDestoryed();
}

