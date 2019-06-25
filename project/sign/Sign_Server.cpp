#include "Arp.h"
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
void error_msg(string msg) {
    cout << msg << "errno" << endl;
    exit(0);
}

int main()
{
    //读缓冲区
    unsigned char buf[1024];
    int len = 0;
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

    //添加listenfd
    epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN;
    //改为边缘触发模式
    event.events |= EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&event) < 0) {
        close(listenfd);
        error_msg("add listenfd to epollfd");
    }

    while(true) {
        epoll_event events[1024];
        int n = epoll_wait(epollfd,&events[0],1024,1000);
        if(n < 0) {
            if(errno == EINTR)
                continue;
            break;
        }
        else if(n == 0) {
            //超时,继续
            continue;
        }
        else {
            for(int i = 0;i < n;++i) {
                //监听套接字有可读事件
                if(events[i].data.fd == listenfd) {
                    sockaddr_in sockaddr;
                    socklen_t socklen = sizeof(sockaddr);
                    int clientfd = accept(listenfd,(struct sockaddr*)&sockaddr,&socklen);
                    if(clientfd > 0) {
                        //将客户端套接字可读事件注册到epollfd中
                        epoll_event event;
                        event.data.fd = clientfd;
                        event.events = EPOLLIN;
                        event.events |= EPOLLET;

                        if(epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&event) < 0) {
                            close(clientfd);
                            cout << "add clientfd error" << endl;
                        }

                    }

                }
                //客户端套接字有可读事件
                else {
                    len = recv(events[i].data.fd,buf,1,0);
                    if(len == 0) {
                        //连接已关闭
                        //从epollfd中删除
                        if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,NULL) != -1) {
                            cout << "client:" << events[i].data.fd << " closed" << endl;
                        }
                        close(events[i].data.fd);
                    }
                    else if(len < 0) {
                        if(errno != EWOULDBLOCK && errno != EINTR) {
                            if(epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,NULL) != -1) {
                                cout << "client:" << events[i].data.fd << " closed" << endl;
                            }
                            close(events[i].data.fd);
                        }
                    }
                    else {
                        //发送arp请求
                        Arp SendArp;
                        string dst = SendArp.GetIpAddr();
                        dst = dst.substr(0,dst.rfind(".",dst.length()-1)+1);
                        struct sockaddr_ll arp_addr = SendArp.GetAddr();
                        char *buf_send;

                        int sockfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));
                        if(sockfd < 0) {
                            cout << "create raw socket error" << endl;
                            exit(0);
                        }    

                        for(int i = 1;i < 256;++i) {
                            dst += to_string(i);
                            SendArp = dst;
                            buf_send = SendArp.ArpFill();
                            sendto(sockfd, buf_send, ETHER_ARP_PACKET_LEN, 0, (struct sockaddr *)(&arp_addr), sizeof(struct sockaddr_ll));
                        }
                    }
                }
            }
        }
    }

    return 0;
}

