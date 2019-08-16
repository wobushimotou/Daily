#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "chat.h"

using namespace std;

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0) {
        cout << "套接字创建失败" << endl;
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.3.122");
    servaddr.sin_port = htons(8000);

    int size = 0;
    socklen_t len = sizeof(size);    
    while(1) {
        int connfd = socket(AF_INET,SOCK_STREAM,0);
        if(connect(connfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
            cout << "连接失败" << " ";
        }
        else
            cout << "连接成功" << " ";

   }
    int connfd;
    char buf[100000];
    int n = send(connfd,buf,100000,0);
 

    //setsockopt(fd,SOL_SOCKET,SO_LINGER)
   
    close(fd);
    return 0;
}

