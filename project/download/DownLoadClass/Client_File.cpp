#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <iostream>
#include "Thread_Recv_Send.h"

using namespace std;

int IsConnect(int &fd) {
    struct tcp_info info;
    int len = sizeof(info);
    getsockopt(fd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&len);

    if(info.tcpi_state == TCP_ESTABLISHED) {//连接未断开
        std::cout << "连接未断开" << std::endl;
        return 1;
    }
    else {
        std::cout << "连接已断开" << std::endl;
        fd = socket(AF_INET,SOCK_STREAM,0);

        if(fd < 0) {
            cout << "套接字创建失败" << endl;
            exit(0);
        }

        struct sockaddr_in servaddr;
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(5678);

        if(connect(fd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
            cout << "连接失败" << endl;
            return 0;
        }
        return 1;
    }
}
int main()
{
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    if(sock_fd < 0) {
        cout << "套接字创建失败" << endl;
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(5678);

    if(connect(sock_fd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
        cout << "连接失败" << endl;
        exit(0);
    }

    char ch;
    cin >> ch;
    if((IsConnect(sock_fd)) == 1) {
        write(sock_fd,&ch,1);
    }   

    close(sock_fd); 

    return 0;
}

