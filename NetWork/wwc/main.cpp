#include <iostream>
#include <string.h>
#include "./log/log.h"
#include "EventLoop.h"
#include <sys/timerfd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
EventLoop loop;
void f() {
    std::cout << "readableing" << std::endl;
    loop.quit();
}

int main()
{
        //创建监听套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0); 
    if(listenfd < 0) {
        exit(0);
    }

    //设置重用ip地址和端口
    int flag = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&flag,sizeof(flag));

    //设置监听套接字为非阻塞
    //获取当前文件标志，与新标志合并后再设置
    flag = fcntl(listenfd,F_GETFL,0);
    flag |= O_NONBLOCK;
    if(fcntl(listenfd,F_SETFL,flag) < 0) {
        close(listenfd);
        exit(0);
    } 

    //初始化服务器地址
    struct sockaddr_in sockaddr;
    sockaddr.sin_port = htons(8891);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htons(INADDR_ANY);

    if(bind(listenfd,(struct sockaddr *)&sockaddr,sizeof(struct sockaddr)) < 0) {
        close(listenfd);
        exit(0);
    }
    
    //启动监听
    if(listen(listenfd,SOMAXCONN) < 0) {
        close(listenfd);
        exit(0);
    }


    Channel channel(&loop,listenfd);
    channel.setReadCallback(f);
    channel.enableReading();


    loop.loop();
    return 0;
}

