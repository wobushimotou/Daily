#include "EventLoop.h"
#include "TcpServer.h"
#include "EventLoopThreadPool.h"
#include "Buffer.h"
#include <signal.h>
#include <fstream>
void signal_handle(int signal_num) {
    printf("非正常退出\n");
}

void signal_handle2(int sig_num) {
    printf("错误退出,当前线程id为%ld",syscall(SYS_gettid));
    exit(0);
}
using namespace std;

void onConnection1(std::shared_ptr<TcpConnection> conn) {
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

    /* std::shared_ptr<EventLoop> loop(new EventLoop()); */
    /* HttpServer server2(loop,9999,"wang"); */
    /* server2.start(); */
    /* loop->loop(); */

    EventLoopThreadPool ep;
    ep.setThreadNum(10);
    ep.start();
    return 0;
}

