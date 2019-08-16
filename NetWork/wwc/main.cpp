#include "EventLoop.h"
#include "TcpServer.h"
#include "Buffer.h"
#include "HttpServer.h"
#include <signal.h>
#include <fstream>
void signal_handle(int signal_num) {
    printf("非正常退出\n");
    exit(0);
}

using namespace std;
EventLoop loop;

void onConnection1(std::shared_ptr<TcpConnection> conn) {
    printf("onConnection():new connection\n");
}

void Construct(string &s,string &head);
void onMessage1(std::shared_ptr<TcpConnection> conn,Buffer *data,size_t n) {
    std::string buff;
    data->retrieveAllAsString(buff);
    buff.clear();
    string head;

    Construct(buff,head);
    conn->send(head);
    conn->send(buff);   
    buff.clear();
}

void onMessage2(std::shared_ptr<TcpConnection> conn,Buffer *data,size_t n) {
    std::string buff;
    data->retrieveAllAsString(buff);
    conn->send(buff);
}


void Construct(string &s,string &head) {
    //构造响应头
    fstream file("./test.html") ;
    int i = 0;
    char ch;
    while(file.read(&ch,1)) {
        s.push_back(ch);
        ++i;
    }
    s += "\r\n\r\n";

    head = string("HTTP/1.1 200 OK\r\n")+ \
           "Content-Type: text/html;charset=utf-8\r\n"+ \
            "Content-Length: "+to_string(i) + "\r\n"+ \
            "Connection: keep-alive\r\n" + \
            "Cache-Control:max-age=-1\r\n" + \
            "Server: nginx/1.8.0\r\n"+"\r\n";
}
int main()
{
    HttpServer server2(&loop,9999,"wang");
    
    server2.start();
    

    loop.loop();
    return 0;
}

