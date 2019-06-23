#include "Arp.h"
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
void error_msg(string) {
    cout << msg << "errno" << endl;
    exit(0);
}

int main()
{
    char buf[1024];
    //申请监听套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd < 0) {
        error_msg("create listenfd ");
    }

    //设置ip和端口重用
    int flag = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&flag,sizeof(flag));

    //将监听套接字设置为非阻塞
    flag = fcntl(listenfd,F_GETFL,0);
    flag |= O_NONBLOCK;
    if(fcntl(listenfd,F_SETFL,flag) < 0) {
        close(listenfd);
        error_msg("set listenfd to nonblock ");
    }
    
    //设置服务器ip和端口
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(SERVER_PORT);
    sockaddr.sin_addr.s_addr = htons(INADDR_ANY); 
    
    if(bind(listenfd,(struct sockaddr *)&sockaddr,sizeof(struct sockaddr)) < 0) {
        close(listenfd);
        error_msg("bind ");
    }

    if(listen(listenfd,SOMAXCONN) < 0) {
        close(listenfd);
        error_msg("listen ");
    }

    //创建epollfd
    int epollfd = epoll_create(1);
    if(epollfd < 0) {
        close(listenfd);
        error_msg("creatae epollfd ");
    }

    return 0;
}

