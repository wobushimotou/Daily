#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#define SERVER_PORT 8888
using namespace std;

int main()
{
    //创建监听套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0); 
    if(listenfd < 0) {
        cout << "create listenfd error" << endl;
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
        cout << "set listenfd to nonblock error" << endl;
        exit(0);
    } 

    //初始化服务器地址
    struct sockaddr_in sockaddr;
    sockaddr.sin_port = htons(SERVER_PORT);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htons(INADDR_ANY);

    if(bind(listenfd,(struct sockaddr *)&sockaddr,sizeof(struct sockaddr)) < 0) {
        close(listenfd);
        cout << "bind listenfd sockaddr error" << endl;
        exit(0);
    }
    
    //启动监听
    if(listen(listenfd,SOMAXCONN) < 0) {
        close(listenfd);
        cout << "listen error" << endl;
        exit(0);
    }

    //创建epollfd
    int epollfd = epoll_create(1);
    if(epollfd == -1) {
        close(listenfd);
        cout << "create epollfd error" << endl;
        exit(0);
    }

    //将监听套接字绑定到epollfd上面
    epoll_event event;
    event.data.fd = listenfd;
    event.events = EPOLLIN;
    event.events |= EPOLLET;
    

    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&event) < 0) {
        close(listenfd);
        cout << "epoll_ctl error" << endl;
        exit(0);
    }
    
    while(true) {
        epoll_event epoll_event[1024];
        int n = epoll_wait(epollfd,epoll_event,1024,1000);
        if(n < 0) {
            //被信号中断
            if(errno == EINTR)
                continue;
            break;
        }
        else if(n == 0) {
            //超时，继续
            continue;
        }
        else {
            for(int i = 0;i < n;++i) {
                //有事件可读
                if(epoll_event[i].events & EPOLLIN) {
                    //监听套接字可读
                    if(epoll_event[i].data.fd == listenfd) {
                        struct sockaddr_in clientaddr;
                        socklen_t clientaddrlen = sizeof(struct sockaddr);
                        int clientfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clientaddrlen);
                        if(clientfd > 0) {
                            //将客户端套接字转换为非阻塞
                            int flag = fcntl(clientfd,F_GETFL,0);
                            flag |= O_NONBLOCK;
                            if(fcntl(clientfd,F_SETFL,flag) < 0) {
                                close(clientfd);
                                cout << "set clientfd nonblock error" << endl;
                            }
                            else {
                                //将clientfd添加进epollfd中
                                struct epoll_event event_client;
                                event_client.data.fd = clientfd;
                                event_client.events = EPOLLIN;
                                event_client.events |= EPOLLET;
                            
                                if(epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&event_client) < 0) {
                                    close(clientfd);
                                    cout << "clientfd add to epollfd error" << endl;
                                }
                                else {
                                    cout << "clientfd add to epollfd success" << endl;
                                }
                            }
                        }
                        
                    }
                    //客户端套接字可读
                    else {
                        char ch;
                        int len = recv(epoll_event[i].data.fd,&ch,1,0);
                        if(len == 0) {
                            //连接已关闭
                            //从epollfd中删除此套接字
                            if(epoll_ctl(epollfd,EPOLL_CTL_DEL,epoll_event[i].data.fd,NULL) != -1) {
                                cout << "client closed clientfd:" << epoll_event[i].data.fd << endl;;
                            }
                            close(epoll_event[i].data.fd);
                        }
                        else if(len < 0) {
                            //出错
                            if(errno != EWOULDBLOCK && errno != EINTR) {
                                close(epoll_event[i].data.fd);
                                if(epoll_ctl(epollfd,EPOLL_CTL_DEL,epoll_event[i].data.fd,NULL) != -1) {
                                    cout << "client closed clientfd:" << epoll_event[i].data.fd << endl;;
                                }
                                close(epoll_event[i].data.fd);
                            }
                        }
                        else {
                            cout << "clientfd: " << epoll_event[i].data.fd << " recv data:" << ch <<  endl;
                        }
                    }
                }else if(epoll_event[i].events & EPOLLERR) { 
                
                    //暂不处理
                }
            }
            
        }
    }
    close(listenfd);
    return 0;
}

